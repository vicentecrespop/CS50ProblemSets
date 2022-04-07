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
    //size os rows the pyramid is going to have
    int length = (height * 2) + 3;
    for (int i = 1; i <= height; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (j < (height - i) || (j > height && j <= height + 2))
            {
                printf(" ");
            }
            //prints "#" if the row is greater or equal then the height minus the respective line of the pyramid and if the row is before the spaces
            else if (j >= (height - i) && j < height)
            {
                printf("#");
            }
            //prints "#" if the row is after the spaces and if the rows is less or equal to after the spaces plus the respective line of the pyramid
            else if (j > (height + 2) && j <= (height + i) + 2)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}