#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <cs50.h>

float get_words(string text);
float get_average_letters(string text);
float get_average_sentences(string text);
int get_index(string text);

int main(void)
{
    //USE TEXT INPUT
    string text;
    text = get_string("Text :");

    //PRINTS THE GRADE OF THE TEXT
    if (get_index(text) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (get_index(text) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", get_index(text));
    }
}

//FUNCTION TO CALCULATE THE AMOUNT OF WORDS IN THE TEXT
float get_words(string text)
{
    float words = 1;
    int length = strlen(text); //LENGTH OF THE ARRAY
    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return words;

}

//FUNCTION TO CALCULATE THE AMOUNT OF LETTERS IN THE TEXT
float get_average_letters(string text)
{
    int length = strlen(text); //LENGTH OF THE ARRAY
    float letters = 0;
    float average_letters;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    average_letters = ((float)letters * 100) / get_words(text);
    return average_letters;
}
//FUNCTION TO CALCULATE THE AMOUNT OF SENTENCES IN THE TEXT
float get_average_sentences(string text)
{
    int length = strlen(text); //LENGTH OF THE ARRAY
    float sentences = 0;
    float average_sentences;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') //PUNCTUATION CHARACTERS
        {
            sentences++;
        }
    }
    average_sentences = (sentences * 100) / get_words(text);
    return average_sentences;


}
//COLEMAN-LIAU INDEX FORMULA
int get_index(string text)
{
    float index = (0.0588 * get_average_letters(text)) - (0.296 * get_average_sentences(text)) - 15.8;
    return round(index);
}