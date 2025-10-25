#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool alpha(string ch);
bool repeat(string chp);
void cypher(string ch, string key, string cipherText);
int findIndex(char x, char keys[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("key must contain 26 characters.\n");
        return 1;
    }
    else if (!alpha(argv[1]))
    {
        printf("key mist only contain alphabetic characters.\n");
        return 1;
    }
    else if (repeat(argv[1]))
    {
        printf("key must not contain repeated characters.\n");
        return 1;
    }
    else
    {
        string text = get_string("plaintext: ");
        char result[strlen(text)];
        cypher(text, argv[1], result);
        printf("ciphertext: %s\n", result);
        return 0;
    }
}

bool alpha(string ch)
{
    int length = strlen(ch);
    int i = 0;
    while (i < length)
    {
        if (!isalpha(ch[i]))
        {
            return false;
        }
        i++;
    }
    return true;
}

bool repeat(string chp)
{
    int length = strlen(chp);
    char ch[length];
    for (int k = 0; k < length; k++)
    {
        ch[k] = toupper(chp[k]);
    }

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (ch[i] == ch[j])
            {
                return true;
            }
        }
    }
    return false;
}

void cypher(string ch, string key, string cipherText)
{
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                       'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    int length = strlen(key);
    char uniKey[length];
    for (int k = 0; k < length; k++)
    {
        uniKey[k] = toupper(key[k]);
    }

    int textLength = strlen(ch);

    for (int i = 0; i < textLength; i++)
    {
        if (!isalpha(ch[i]))
        {
            cipherText[i] = ch[i];
        }
        else
        {
            if (islower(ch[i]))
            {
                cipherText[i] = (char) uniKey[findIndex(toupper(ch[i]), alphabet)] + 32;
            }
            else
            {
                cipherText[i] = (char) uniKey[findIndex(toupper(ch[i]), alphabet)];
            }
        }
    }
    cipherText[textLength] = '\0';
}

int findIndex(char x, char keys[])
{
    int i = 0;
    while (i < 26)
    {
        if (x == keys[i])
        {
            return i;
        }
        else
        {
            i++;
        }
    }
    return x;
}
