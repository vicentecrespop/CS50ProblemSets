#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    //Keep asking for the height if the height given isn't between 1 - 8 or a number
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int i = 2; i <= height + 1 ; i++)
    {
        for (int j = 0; j < height ; j++)
        {
            if (j > (height - i))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}