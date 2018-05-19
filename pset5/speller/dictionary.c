/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

int function_hash(const char* word);

typedef struct node
{
    struct node* sgte;
    char *valor;
} node;


node *dict[26];
int count=0;
char word[LENGTH];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int pos=function_hash(word);

    node* aux = dict[pos];

    while(aux!=NULL)
    {
        //COMPARE IN CASE INSENSITIVE FORMAT
        if (strcasecmp(aux->valor, word) == 0)
            return true;
        aux=aux->sgte;
    }

    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{

    FILE* file = fopen(dictionary,"r");

    if(file==NULL)
    {
        return false;
    }

    while (fscanf(file, "%s\n", word) != EOF)
    {
        int pos = function_hash(word);

        node* aux = malloc(sizeof(node));
        aux->valor=malloc(strlen(word));

        strcpy(aux->valor,word);

        if(dict[pos]==NULL)
        {
            dict[pos]=aux;
            aux->sgte=NULL;
        }
        else
        {
            aux->sgte=dict[pos];
            dict[pos]=aux;
        }

        count++;
    }

    fclose(file);
    return true;


}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 * FREE MEMORY HASH
 */
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *cursor = dict[i];

        while (cursor!=NULL)
        {
            node* tmp = cursor;
            cursor = cursor->sgte;
            free(tmp);
            return true;
        }

        dict[i] = NULL;
    }

    return false;
}

int function_hash(const char* word)
{
    //THIS FUNCTION RETURN A VALUE BETWEEN 0 AND 25 (A-Z) LIKE A REAL DICTIONARY
    return tolower(*word+0)%26 ;
}