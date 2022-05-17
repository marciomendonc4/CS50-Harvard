#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    //COLLECTING NUMBER BETWEEN 1 AND 8
    do
    {
        n = get_int("Height: \n");
    }
    while (n < 1 || n > 8);
    
    //main loop
    
    for (int i = 0; i < n; i++)
    {
        //making the first pyramid
        
        for (int j = n - 1; j > i; j--)
        {
            printf(" ");
        }
         
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        
        //blankspace between
        
        printf("  ");
        
        //second pyramid    
         
        for (int j = n - 1; j >= n; j--)
        {
        
            printf(" ");
        }
         
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        
        // breaking lines 
        printf("\n");
        
    }
    
}