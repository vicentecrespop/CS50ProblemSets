#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int only_letters(string letters[]);
string rotate(string key[], string text);


int main(int argc, string argv[])
{
    if (argc != 2 || !only_letters(argv))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc == 2 && only_letters(argv))
    {
        string key = argv[1];
        int argv_len = strlen(key);
        int count = 0;
        if (argv_len == 26)
        {
            for (int i = 0; i < 26; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    if (toupper(key[i]) == toupper(key[j]))
                    {
                        count++;
                    }
                }
            }
            if (count == 26)
            {
                string plaintext = get_string("plaintext:  ");
                string ciphertext = rotate(argv, plaintext);
                printf("ciphertext: %s", ciphertext);
            }
            else
            {
                printf("Key contains duplicate characterers.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 characteres.");
            return 1;
        }
    }
    printf("\n");
}
//Converts text to ciphertext
string rotate(string key[], string text)
{
    int key_len = strlen(key[1]);
    string key_text = key[1];
    char cipher;
    int key_num[key_len];
    int text_len = strlen(text);
    for (int i = 0; i < key_len; i++)
    {
        cipher = toupper(key_text[i]);
        key_num[i] = ((int) cipher) - 65;
    }
    for (int i = 0; i < text_len; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                int textNum = ((int) text[i]) - 65;
                textNum = key_num[textNum] + 65;
                text[i] = (char) textNum;
            }
            else
            {
                int textNum = ((int) text[i]) - 97;
                textNum = key_num[textNum] + 97;
                text[i] = (char) textNum;
            }
        }
    }
    return text;
}

//Checks if string is a number
int only_letters(string letters[])
{
    int len = strlen(letters[1]);
    string key = letters[1];
    for (int i = 0; i < len; i++)
    {
        if (isalpha(key[i]) == false)
        {
            return 0;
        }
    }
    return 1;
}
