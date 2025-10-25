#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("type the height: ");
    }
    while (height < 1);

    int i = 0;
    while (i < height)
    {
        for (int k = 0; k < height - i - 1; k++)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
        i++;
    }
}
