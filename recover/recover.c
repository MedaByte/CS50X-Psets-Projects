#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE uint8_t
#define BLOCKSIZE 512

char *makeName(int n);

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Error: File not found\n");
        return 1;
    }

    // Create a buffer for a block of data
    BYTE buffer[BLOCKSIZE];

    int photoNum = 0;

    // create first file
    char *name = "000.jpg";
    FILE *img = fopen(name, "w");
    if (img == NULL)
    {
        printf("Error: could not open file\n");
        return 1;
    }
    fclose(img);
    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCKSIZE, card) == BLOCKSIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // checking for previous files
            if (photoNum != 0)
            {
                fclose(img);
            }

            // name formating
            name = malloc(sizeof(char) * (strlen("###.jpg") + 1));
            sprintf(name, "%.3i.jpg", photoNum);

            // file creation
            img = fopen(name, "w");
            fwrite(buffer, 1, BLOCKSIZE, img);

            // prepare for the next file name
            photoNum++;

            // free the allocated memory for this iteration
            free(name);
        }
        else
        {
            // checking if read jpg
            if (photoNum != 0)
            {
                fwrite(buffer, 1, BLOCKSIZE, img);
            }
        }
    }
    // closing remaining files
    fclose(card);
    fclose(img);
}
