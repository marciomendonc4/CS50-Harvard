#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

void cipher(int k, string text); //TELLING THE COMPILER THAT THIS FUNCTION IS GOING TO BE CALLED LATER

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int len = strlen(argv[1]);
        //LOOP THAT GOES THROUGH THE ARGV[1] CHARACTERS
        for (int c = 0; c < len; c++) 
        {
            if (isalpha(argv[1][c])) //IF IT FINDS A LETTER
            {
                printf("Usage: ./caesar key\n");
                return 1; //RETURNING 1 TO MAIN
            }
        }
        string plaintext = get_string("plaintext: ");
        int key = atoi(argv[1]);
        cipher(key, plaintext);
        printf("\n");
    }
    //IF ARGV[1] HAS MORE (OR LESS) THAN ONE ARGUMENT
    else
    {
        printf("Usage: ./caesar key\n"); 
        return 1; //RETURNING 1 TO MAIN
    }
}
//FUNCTION USED TO ENCIPHER THE PLAINTEXT
void cipher(int k, string text)
{
    int length = strlen(text);
    char ciphertext[1000];
    
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i])) //UPPERCASE LETTERS
            {
                int cipher = ((text[i] - 65) + k) % 26; //USING ASCII VALUES
                ciphertext[i] = 65 + cipher;
            }
            else if (islower(text[i])) //LOWERCASE LETTERS
            {
                int cipher = ((text[i] - 97) + k) % 26; //USING ASCII VALUES
                ciphertext[i] = 97 + cipher;
            }
            else if (isspace(text[i]))
            {
                continue;
            }
        }
        else
        {
            ciphertext[i] = text[i];
        }
        
    }
    printf("ciphertext: %s", ciphertext); //PRINTING THE ENCRYPTED TEXT WHEN THE FUNCTION IS CALLED
    
}