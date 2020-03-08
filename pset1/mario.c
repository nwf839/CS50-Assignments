/* Program that prompts user for an integer height, and prints a half pyramid
   consisting of height rows (up to 23).
   
   Reprompts the user if a non-integer value is entered, a negative value is
   is entered, or an integer higher than 23 is entered                       */
   
#include <stdio.h>
#include <cs50.h>
   
int main(void)
{
    int height, i, j, k;
    
    printf("Height: ");
    height = GetInt();
     
     
    // Reprompts user for height if not integer between 0 and 23
    
    while (height < 0 || height > 23)  
    {
        printf("Height: ");
        height = GetInt();
    }
    
    // Prints pattern of characters using nested loops
    
    for (i = 1; i <= height; i++)
    {   
        for (k = height; k > i; k++)
        {
            printf(" ");
        }
        
        for (j = 0; j <= i; j++)
        {
            printf("#");
        }
        
        printf("\n");
    }
    
    return 0;
}
