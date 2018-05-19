import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        Positive_file = open(positives, 'r')
        self.positives  = []

        for word in Positive_file.read().splitlines():
            if not word.startswith(';'):
                self.positives.append(word)

        Positive_file.close()

        Negative_file = open(negatives, 'r')
        self.negatives  = []

        for word in Negative_file.read().splitlines():
            if not word.startswith(';'):
                self.negatives.append(word)
        Negative_file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        score = 0
        text = text.lower()

        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)

        for word in tokens:
            if word in self.positives:
                score += 1
            elif word in self.negatives:
                score -= 1


        return score

