/*  vigenere.c
    
    Program that takes string of alphabetic characters as key, assigns
    a value between 1 and 26 to each character based on respective
    positions in alphabet, and performs a Caesar rotation of that number
    when lined up with a string that the user is prompted for.
    
    If the key is shorter than the number of alphabetic characters in
    the string, the key goes back to the first position until all
    characters in the string are enciphered                             */
    
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    // Exits with error code 1 if incorrect number of arguments entered
    if (argc != 2)
    {
        printf("Program must be executed with one command-line argument.\n");
        return 1;
    }
    
    string key = 0;
    string pText = 0;
    char caesar(char letter, int keyNum);
    char cipher = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int arrayCounter = 0;
    int keyLen = 0;
    int pTextLen = 0;
    
    // Precalculates upper bound of loop before execution
    key = argv[1];
    keyLen = strlen(key);
    
    // Exits with error code 1 if key contains non-alphabetic characters
    for (i = 0; i < keyLen; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must only consist of alphabetic characters");
            return 1;
        }
    }
    
    // Creates array of numbers representing rotation number for each position
    int keyArray[keyLen];
    
    for (j = 0; j < keyLen; j++)
    {
        if (key[j] >= 65 && key[j] <= 90)
        {
            keyArray[j] = key[j] - 65;
        }
        if (key[j] >= 97 && key[j] <= 122)
        {
            keyArray[j] = key[j] - 97;
        }
    }
    
    // Get string from user and precalculates upper bound for loop
    pText = GetString();
    pTextLen = strlen(pText);
    
    // Loops values from string and array of keys into caesar function
    for (k = 0; k < pTextLen; k++)
    {    
        if (isalpha(pText[k]))
        {
            cipher = caesar(pText[k], keyArray[arrayCounter % keyLen]);
            printf("%c", cipher);
            arrayCounter++;
        }
        else
        {
            printf("%c", pText[k]);
        }
    }
    
    printf("\n");
    
    return 0;
}

// Function definition for caesar
char caesar(char letter, int keyNum)
{
    int cipher = 0;
    int cTemp = 0;
    
    cTemp = letter + keyNum;
    
    // Wraps lowercase letter to beginning of alphabet
    if (letter >= 65 && letter <= 90 && cTemp > 90)
    {
        cipher = cTemp % 90 + 64;
    }
    
    // Wraps uppercase letters to beginning of alphabet
    else if (letter >= 97 && letter <= 122 && cTemp > 122)
    {
        cipher = cTemp % 122 + 96;
    }
    
    // Enciphers if wrapping isn't necessary
    else
    {
        cipher = cTemp;
    }
    
    return cipher;
}
