#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    // CHECKING IF THE USER TYPED MORE THAN 1 COMMAND LINE ARGUMENT
    if (argc != 2)
    {
        printf("./substitution key\n");
        return 1;
    }
    int length = strlen(argv[1]);
    if (length != 26) // IF THE AMOUNT OF CHARACTERS IS DIFFERENT THAN 26
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        //CHECKING FOR DIGITS AND REPEATED LETTERS
        for (int i = 0; i < length; i++)
        {
            if (isdigit(argv[1][i]))
            {
                printf("Key must contain only aphabetical characters.\n");
                return 1;
            }
        }
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = i + 1; j <= length; j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Your key contains repeated letter(s).\n");
                    return 1;
                }
            }
            
        }
    }
    //VARIABLES USED
    string plaintext = get_string("plaintext: ");
    int text_length = strlen(plaintext);
    char ciphertext [text_length + 1];
    
    //LOOP THAT GOES THROUGH THE TEXT INPUT
    for (int i = 0; i <= text_length; i++)
    {
        
        if (i == text_length)
        {
            ciphertext[i] = '\0';
        }
        if (isalpha(plaintext[i])) // ONLY ALPHABETICAL CHARACTERS ARE ANALYZED
        {
            if (isupper(plaintext[i]))
            {
                int cipher = (plaintext[i] - 65);
                ciphertext[i] = toupper(argv[1][cipher]);
            }
            else if (islower(plaintext[i]))
            {
                int cipher = (plaintext[i] - 97);
                ciphertext[i] = tolower(argv[1][cipher]);
            }
            else if (isspace(plaintext[i]))
            {
                continue;
            }
        }
        else //IF ANY CHARACTER BUT ALPHABETICAL
        {
            ciphertext[i] = plaintext[i];
        }
    }
    //ENCRYPTED TEXT OUTPUT
    printf("ciphertext: %s\n", ciphertext); 
    
}
