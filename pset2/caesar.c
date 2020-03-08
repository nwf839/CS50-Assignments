/*  Takes integer as command-line argument, prompts user for string,
    and rotates each character of string by the number entered as
    command-line argument                                           */
    
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Exits with error code 1 if wrong number of arguments entered
    if (argc != 2)
    {
        printf("Program must be executed with one command-line argument\n");
        return 1;
    }
    
    int key = atoi(argv[1]);
    string pText = GetString();
    int cipher = 0;
    int cTemp = 0;
    int i = 0;
    
    key %= 26;
    
    // Manipulates ascii codes of characters in string
    for (i = 0; i < strlen(pText); i++)
    {
        cTemp = pText[i] + key;
        
        // Keeps non-alphabetic characters constant
        if (pText[i] < 65 || (pText[i] > 90 && pText[i] < 97) || pText[i] > 122)
        {
            cipher = pText[i];
        }
        
        // Wraps uppercase letters to beginning of alphabet
        else if (pText[i] >= 65 && pText[i] <= 90 && cTemp > 90)
        {
            cipher = cTemp % 90 + 64;
        }
        
        // Wraps lowercase letters to beginning of alphabet
        else if (pText[i] >= 97 && pText[i] <= 122 && cTemp > 122)
        {
            cipher = cTemp % 122 + 96;
        }
        
        // Enciphers string character
        else
        {
            cipher = cTemp;
        }
        
        // Prints resultant ascii code as character for each iteration
        printf("%c", cipher);
    }
    
    printf("\n");
    
    return 0;
}
