#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int only_digits(string number[]);
char rotate(char text, int k);


int main(int argc, string argv[])
{

    if (argc == 2 && only_digits(argv))
    {
        //Converts string argv[1] to int key
        int key = atoi(argv[1]);
        string plaintext = get_string("plaintext:  ");
        int len = strlen(plaintext);
        char ciphertext[len];
        printf("ciphertext: ");
        for (int i = 0; i < len; i++)
        {
            ciphertext[i] = rotate(plaintext[i], key);
            printf("%c", ciphertext[i]);
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    printf("\n");
}
//Converts text to ciphertext
char rotate(char text, int k)
{
    if (isalpha(text))
    {
        if (isupper(text))
        {
            int textNum = ((int) text) - 65;
            int cipherNum = ((textNum + k) % 26) + 65;
            text = (char) cipherNum;
        }
        else
        {
            int textNum = ((int) text) - 97;
            int cipherNum = ((textNum + k) % 26) + 97;
            text = (char) cipherNum;
        }
    }
    return text;
}



//Checks if string is a number
int only_digits(string number[])
{
    int len = strlen(number[1]);
    string valor = number[1];
    int test = 0;
    for (int i = 0; i < len; i++)
    {
        if (valor[i] >= 48 && valor[i] <= 57)
        {
            test++;
        }
    }
    if (test == len)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}