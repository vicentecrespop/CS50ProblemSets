#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Get text from user.
    string text = get_string("Text: ");

    //Calculating the number of letters.
    int letters = count_letters(text);

    //Calculating the number of words.
    int words = count_words(text);

    //Calculating the number of sentences.
    int sentences = count_sentences(text);

    float L = ((float) letters * 100) / (float) words;
    float S = ((float) sentences * 100) / (float) words;

    //Using the Coleman-Liau index.
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int index_int =  index;
    if ((index - index_int) > 0.5)
    {
        index_int++;
    }
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index_int);
    }

}

int count_letters(string text)
{
    int length = strlen(text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int length = strlen(text);
    int count = 1;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int length = strlen(text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}