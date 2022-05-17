#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


bool validkey(string s); 
void encrypt(string s, string key); 

int main(int argc, string argv[]) 
{
if(argc != 2 || !validkey(argv[1])) 
{
    printf("Invalid\n"); 
    return 1; 
}
string plaintext = get_string("plaintext: "); 
string key = argv[1];
encrypt(plaintext, key);
}

bool validkey(string s) 
{
for(int i= 0; i < strlen(s); i++) 
{
    if(!isalpha(s[i]) || strlen(s)!=26) 
       return false;
}
return true; 
}
void encrypt(string s, string key) 
{
printf("ciphertext: "); 
for(int i = 0; i < strlen(s); i++) 
{
    if(!isalpha(s[i])) // for something other than alphabet 
    {
        printf("%c",s[i]); 
        continue; 
    // encrypting alphabets
    }
    for(int j = 0; j < 26; j++) 
    {
    if(s[i] == 'a' + j) // for lowercase letters 
        printf("%c", tolower(key[j])); 
    else if(s[i] == 'A' + j) // for uppercase letters 
    {
        printf("%c", toupper(key[j])); 
    }
}
}
}
