#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int score(string ch);

int main(int argc, string argv[])
{
    string fst = get_string("player 1: ");
    string scd = get_string("player 2: ");

    if (score(fst) > score(scd))
    {
        printf("player 1 wins!\n");
        return 0;
    }

    else if (score(fst) < score(scd))
    {
        printf("player 2 wins!\n");
        return 0;
    }

    else
    {
        printf("tie!\n");
        return 0;
    }
}

int score(string ch)
{
    int points = 0;
    int charPoints[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int length = strlen(ch);

    for (int i = 0; i < length; i++)
    {
        if ((ch[i] <= 'Z' && ch[i] >= 'A') || (ch[i] <= 'z' && ch[i] >= 'a'))
        {
            points += charPoints[toupper(ch[i]) - 65];
        }
    }

    return points;
}
