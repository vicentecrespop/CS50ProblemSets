#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Checks the number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card
    FILE *image = fopen(argv[1], "r");
    if (image == NULL)
    {
        printf("Could not open image.\n");
        return 1;
    }
    uint8_t buffer[BLOCK_SIZE];
    int file_counter = 0;
    char filename[8];
    FILE *jpeg;
    sprintf(filename, "%03i.jpg", file_counter);
    jpeg = fopen(filename, "w");
    while (fread(buffer, 1, BLOCK_SIZE, image) == BLOCK_SIZE)
    {

        // Checks for beginning of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {

            // Checks if it's the first file
            if (file_counter == 0)
            {
                fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, jpeg);
                file_counter++;
            }

            // If not the first file then close the previous file and open and write on a new file with a new name.
            else
            {
                fclose(jpeg);
                sprintf(filename, "%03i.jpg", file_counter);
                jpeg = fopen(filename, "w");
                fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, jpeg);
                file_counter++;
            }
        }

        //If not the beginnig of a JPEG and a JPEG has already been written then keep writing on the file.
        else if (file_counter > 0)
        {
            fwrite(&buffer, sizeof(uint8_t), BLOCK_SIZE, jpeg);
        }
    }
    fclose(jpeg);
    fclose(image);
}