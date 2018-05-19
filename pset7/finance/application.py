from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from datetime import datetime

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    result = db.execute(
        "SELECT DISTINCT symbol FROM historial where user_id = :id", id=session["user_id"])
    x = []
    stock_total = 0

    for symbol in result:
        x_i = []

        stock = lookup(symbol['symbol'])
        x_i.append(stock.get('name'))

        share_b = db.execute("SELECT SUM(qty) _count FROM historial GROUP BY symbol, action HAVING symbol = :symbol AND action = 0 AND user_id = :id",
                             symbol=stock.get("symbol"), id=session['user_id'])

        share_s = db.execute("SELECT SUM(qty) _count FROM historial GROUP BY symbol, action HAVING symbol = :symbol AND action = 1 AND user_id = :id",
                             symbol=stock.get("symbol"), id=session['user_id'])

        try:
            s_b = share_b[0]['_count']
        except IndexError:
            s_b = 0

        try:
            s_s = share_s[0]['_count']
        except IndexError:
            s_s = 0

        count = s_b - s_s

        if count > 0:
            x_i.append(count)

            x_i.append(stock.get("price"))

            total = count * stock.get("price")
            _total = usd(total)

            x_i.append(_total)

            stock_total += total

            x.append(x_i)

    cash_ = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])

    return render_template("index.html", x=x, cash=usd(cash_[0]["cash"]), stock_total=usd(stock_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        try:
            symbol = request.form.get("symbol")
            qty = int(request.form.get("shares"))
        except ValueError:
            return apology("must be share a positive number")

        # ensure username was submitted
        if not symbol:
            return apology("must provide symbol")

        # ensure password was submitted
        elif not lookup(symbol):
            return apology("must exit symbol")
        elif qty <= 0:
            return apology("must be share a positive number")

        stock = lookup(symbol)

        # query database actual cash of user
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        _cash = cash[0]['cash']

        price = stock.get("price")

        if _cash < qty * price:
            return apology("must be enough cash")

        # query database for insert the buy
        db.execute("INSERT INTO historial (user_id, symbol, qty, datetime, action, price_ancient)"
                   + "VALUES(:id, :sybl, :qty, :dt, 0, :price_ancient)", id=session["user_id"], sybl=symbol, qty=qty, dt=datetime.now().strftime("%Y-%m-%d %H:%M:%S"), price_ancient=price)

        db.execute("UPDATE users set cash = cash - :minus_total WHERE id = :id",
                   minus_total=qty * price, id=session["user_id"])

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    result = db.execute(
        "SELECT DISTINCT symbol FROM historial where user_id = :id", id=session["user_id"])
    x = []

    for symbol in result:

        stock = lookup(symbol['symbol'])

        stock = db.execute("SELECT action, datetime, symbol, SUM(qty) _count, price_ancient FROM historial GROUP BY symbol, action HAVING symbol = :symbol AND user_id = :id",
                           symbol=stock.get("symbol"),
                           id=session['user_id'])

        for st in stock:
            x_i = []

            if st['action'] == 0:
                x_i.append("BUY")
            else:
                x_i.append("SELL")

            x_i.append(st['datetime'])

            x_i.append(st['symbol'])

            _count = st['_count']
            x_i.append(_count)

            _price = st['price_ancient']
            x_i.append(_price)

            total = _count * _price
            x_i.append(usd(total))

            x.append(x_i)

    return render_template("history.html", x=x)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        rows = lookup(request.form.get("symbol"))

        if not rows:
            return apology("Invalid Symbol")

        rows['price'] = usd(rows['price'])

        return render_template("quoted.html", stock=rows)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure that confirm password
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("must confirm password")

        # query database for i am sure that not exits another same username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        if len(rows) != 0:
            return apology("Username already exist")

        # query database for insert a user
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get(
            "username"), hash=pwd_context.hash(request.form.get("password")))

        # remember which user has logged in

        session["user_id"] = result

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        try:
            symbol = request.form.get("symbol")
            qty = int(request.form.get("shares"))
        except ValueError:
            return apology("must be share a positive number")

        # ensure username was submitted
        if not symbol:
            return apology("must provide symbol")

        # ensure password was submitted
        elif not lookup(symbol):
            return apology("must exit symbol")
        elif qty <= 0:
            return apology("must be share a positive number")

        stock = lookup(symbol)

        # ensure that exit enough shares
        share_b = db.execute("SELECT SUM(qty) _count FROM historial GROUP BY symbol HAVING symbol = :symbol AND action = 0 AND user_id = :id",
                             symbol=stock.get("symbol"), id=session['user_id'])

        share_s = db.execute("SELECT SUM(qty) _count FROM historial GROUP BY symbol HAVING symbol = :symbol AND action = 1 AND user_id = :id",
                             symbol=stock.get("symbol"), id=session['user_id'])

        try:
            s_b = share_b[0]['_count']
        except IndexError:
            s_b = 0

        try:
            s_s = share_s[0]['_count']
        except IndexError:
            s_s = 0

        count = s_b - s_s

        if count <= 0:
            return apology("must be have that stock")
        elif qty > count:
            return apology("must be enough shares")

        stock = lookup(symbol)

        price = stock.get("price")

        # query database for insert the buy
        db.execute("INSERT INTO historial (user_id, symbol, qty, datetime, action, price_ancient)"
                   + "VALUES(:id, :sybl, :qty, :dt, 1, :price)", id=session["user_id"], sybl=stock.get("symbol"), qty=qty, dt=datetime.now().strftime("%Y-%m-%d %H:%M:%S"), price=price)

        db.execute("UPDATE users set cash = cash + :plus_total WHERE id = :id",
                   plus_total=qty * price, id=session["user_id"])

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        x = []
        x_ = db.execute(
            "SELECT DISTINCT symbol FROM historial WHERE action = 0 AND user_id = :id", id=session['user_id'])

        for x_i in x_:
            # ensure that exit enough shares
            share_b = db.execute("SELECT SUM(qty) _count FROM historial GROUP BY symbol HAVING symbol = :symbol AND action = 0 AND user_id = :id",
                                 symbol=x_i.get("symbol"), id=session['user_id'])

            share_s = db.execute("SELECT SUM(qty) _count FROM historial GROUP BY symbol HAVING symbol = :symbol AND action = 1 AND user_id = :id",
                                 symbol=x_i.get("symbol"), id=session['user_id'])

            try:
                s_b = share_b[0]['_count']
            except IndexError:
                s_b = 0

            try:
                s_s = share_s[0]['_count']
            except IndexError:
                s_s = 0

            count = s_b - s_s

            if count > 0:
                x.append(x_i.get("symbol"))

        return render_template("sell.html", x=x)