/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

typedef struct node
{
	bool word;
	struct node* children[27];
} node;

node* root;
node* cursor;
node* checkCursor;
FILE* dict;
char* dictWord;

int wordCount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    checkCursor = root;
	while(*word != 0)
	{
		if (*word == 39)
		{
			if (checkCursor->children[26] == NULL)
			{
				return false;
			}
			else
			{
				checkCursor = checkCursor->children[26];
			}
		}
		else if (*word < 97)
		{
			if (checkCursor->children[*word - 65] == NULL)
			{
				return false;
			}
			else
			{
				checkCursor = checkCursor->children[*word - 65];
			}
		}
		else
		{
			if (checkCursor->children[*word - 97] == NULL)
			{
				return false;
			}
			else
			{
				checkCursor = checkCursor->children[*word - 97];
			}
		}
		word++;
	}
	if (checkCursor->word == true)
	{
		checkCursor = root;
		return true;
	}
	else
	{
		checkCursor = root;
		return false;
	}
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	dict = fopen(dictionary, "r");
    if (dict == NULL)
	{
		return false;
	}
	else
	{
		root = (node *)calloc(1, sizeof(node));
		root->word = false;
		cursor = root;
		int ptrOffset = 0;
		dictWord = (char *)calloc(LENGTH, sizeof(char));
		while(fscanf(dict, "%s", dictWord) == 1)
		{
			ptrOffset = 0;
			while(*dictWord != 0)
			{
				if (*dictWord == 39)
				{
					if (cursor->children[26] == NULL)
					{
						cursor->children[26] = (node *)calloc(1, sizeof(node));
						cursor->children[26]->word = false;
						cursor = cursor->children[26];
					}
					else
					{
						cursor = cursor->children[26];
					}
				}
				else if (*dictWord < 97)
				{
					if (cursor->children[*dictWord - 65] == NULL)
					{
						cursor->children[*dictWord - 65] = (node *)calloc(1, sizeof(node));
						cursor->children[*dictWord - 65]->word = false;
						cursor = cursor->children[*dictWord - 65];
					}
					else
					{
						cursor = cursor->children[*dictWord - 65];
					}
				}
				else
				{
					if (cursor->children[*dictWord - 97] == NULL)
					{
						cursor->children[*dictWord - 97] = (node *)calloc(1, sizeof(node));
						cursor->children[*dictWord - 97]->word = false;
						cursor = cursor->children[*dictWord - 97];
					}
					else
					{
						cursor = cursor->children[*dictWord - 97];
					}
				}
				dictWord++;
				ptrOffset++;
			}
			free(dictWord - ptrOffset);
			dictWord = (char *)calloc(LENGTH, sizeof(char));
			wordCount++;
			cursor->word = true;
			cursor = root;
		}
		free(dictWord);
		return true;
	}
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dict == NULL)
	{
    return 0;
	}
	else
	{
		return wordCount;
	}
}


//Helper
void FreeLastNode(node* ptrToRootNode)
{
    for (int i = 0; i < 27; i++)
    {
        if (ptrToRootNode->children[i] != NULL)
        {
            FreeLastNode(ptrToRootNode->children[i]);
        }
    }
    free(ptrToRootNode);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    FreeLastNode(root);
    fclose(dict);
    return true;
}
