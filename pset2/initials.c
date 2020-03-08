/*  initials.c

    Prompts user for name and prints capitalized initials   */

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    int i = 0;
    int nameLen = 0;
    string name = 0;
    
    name = GetString();
    
    // If input begins with letter, prints that as capitalized first inital
    if (isalpha(name[0]))
    {
        printf("%c", toupper(name[0]));
    }
    
    // Precalculates upper bound of loop before execution
    nameLen = strlen(name);
    
    // Prints all letters after spaces as capitalized initials
    for (i = 0; i < nameLen; i++)
    {
        if (name[i] == ' ' && isalpha(name[i + 1]))
        {
            printf("%c", toupper(name[i + 1]));
        }
    }
    
    printf("\n");
    
    return 0;
}
