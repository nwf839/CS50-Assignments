/* Program that prompts a user for float representing a dollar amount
   and prints the fewest number of coins possible that can add to
   that amount                                                       */   

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int cents = 0, count = 0;
    float n = 0;
    
    printf("Enter amount of change owed: ");
    n = GetFloat() * 100;
    
    // Reprompt in user enters wrong type of data
    while (n < 0)
    {
        printf("Enter amount of change owed: ");
        n = GetFloat() * 100;
    }
    
    // Convert float of dollar value to integer of number of pennies
    cents = (int) round(n);
    
    while (cents > 0)
    {
        // Count quarters
        if (cents >= 25)
        {
            cents -= 25;
            count++;
        }
        
        // Count dimes
        if (cents <= 24 && cents >= 10)
        {
            cents -= 10;
            count++;
        }
        
        // Count nickels
        if (cents <= 9 && cents >= 5)
        {
            cents -= 5;
            count++;
        }
        
        // Count pennies
        if (cents <= 4 && cents >= 1)
        {
            cents -= 1;
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}
