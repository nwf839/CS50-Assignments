#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LENGTH 45

//#include "dictionary.h"


//Global variables


int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        printf("Program takes 1 command argument");
        return 1;
    }
    
    typedef struct node
    {
        bool word;
        struct node* children[27];
    } node;
    
    char* testWord = argv[2];
    node* root = (node *)malloc(sizeof(node));
    node* cursor = root;
    int wordCount = 0;
    char* dictionary = argv[1];
    int nodeCount = 1;
    char* word = (char *)calloc(LENGTH, sizeof(char));
    int ptrOffset = 0;
    FILE* dict = fopen(dictionary, "r");

    while (fscanf(dict, "%s", word) == 1)
    {
        ptrOffset = 0;
        while (*word != 0)
        {
            if (*word == 39)
            {
                if (cursor->children[26] == NULL)
                {
                    cursor->children[26] = (node *)malloc(sizeof(node));
                    cursor = cursor->children[26];
                    nodeCount++;
                }
                else
                {
                    cursor = cursor->children[26];
                }
            }
            else if (*word < 97)
            {
                if (cursor->children[*word - 65] == NULL)
                {
                    cursor->children[*word - 65] = (node *)malloc(sizeof(node));
                    cursor = cursor->children[*word - 65];
                    nodeCount++;
                }
                else
                {
                    cursor = cursor->children[*word - 65];
                }
            }
            else
            {
                if (cursor->children[*word - 97] == NULL)
                {
                    cursor->children[*word - 97] = (node *)malloc(sizeof(node));
                    cursor = cursor->children[*word - 97];
                    nodeCount++;
                }
                else
                {
                    cursor = cursor->children[*word - 97];
                }
            }
            word++;
            ptrOffset++;
        }
        free(word - ptrOffset);
        word = (char *)calloc(LENGTH, sizeof(char));
        cursor->word = true;
        cursor = root;
        wordCount++;
    }
    free(word);
    
    while (*testWord != 0)
    {
        if (*testWord == 39)
        {
            if (cursor->children[26] == NULL)
            {
                return false;
            }
            else
            {
                cursor = cursor->children[26];
            }
        }
        else if (*testWord < 97)
        {
            if (cursor->children[*testWord - 65] == NULL)
            {
                return false;
            }
            else
            {
                cursor = cursor->children[*testWord - 65];
            }
        }
        else
        {
            if (cursor->children[*testWord - 97] == NULL)
            {
                return false;
            }
            else
            {
                cursor = cursor->children[*testWord - 97];
            }
        }
        testWord++;
    }
    if (cursor->word == true)
    {
        cursor = root;
        printf("Matched in dictionary\n");
        return 0;
    }
    else
    {
        cursor = root;
        printf("No match\n");
        return false;
    }
}
