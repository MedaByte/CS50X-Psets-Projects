#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool checksum(long credit);
int dismantling(int n);

int main(int argc, char *argv[])
{
    long card;
    do
    {
        card = get_long("put your credit: ");
    }
    while (card < 0);

    if (checksum(card))
    {
        char ch[17];
        sprintf(ch, "%ld", card);

        if ((int) strlen(ch) == 16 || (int) strlen(ch) == 13)
        {
            if (ch[0] == '4')
            {
                printf("VISA\n");
            }

            else if (ch[0] == '5' && (int) strlen(ch) == 16)
            {
                if (ch[1] == '1' || ch[1] == '2' || ch[1] == '3' || ch[1] == '4' || ch[1] == '5')
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if ((int) strlen(ch) == 15)
        {
            if (ch[0] == '3')
            {
                if (ch[1] == '4' || ch[1] == '7')
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

bool checksum(long credit)
{
    int s = 0;
    bool alt = false;
    while (credit != 0)
    {
        int digit = credit % 10;
        if (alt)
        {
            digit *= 2;
        }
        s += dismantling(digit);
        credit = credit / 10;
        alt = !alt;
    }
    return (s % 10 == 0);
}

int dismantling(int n)
{
    int s = 0;
    while (n != 0)
    {
        s += n % 10;
        n = n / 10;
    }
    return s;
}
