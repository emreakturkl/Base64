#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

static const char table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                             'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                             'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                             'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

static const char pad = '=';

char* base64_encode(char *plain)
{
    unsigned char len = strlen(plain);
    unsigned int size = 0;

    if(len % 3 == 0)
        size = (len / 3) * 4;
    else
        size = (len / 3 + 1) * 4;

    char *buffer = (char *)malloc((size + 1) * sizeof(char));

    char temp[3];
    unsigned int i = 0, j = 0, counter = 0;;

    for(i = 0; plain[i] != '\0'; i++)
    {
        temp[counter++] = plain[i];
        if(counter == 3)
        {
            buffer[j++] = table[temp[0] >> 2];
            buffer[j++] = table[((temp[0] & 0x03) << 4) + (temp[1] >> 4)];
            buffer[j++] = table[((temp[1] & 0x0f) << 2) + (temp[2] >> 6)];
            buffer[j++] = table[temp[2] & 0x3f];
            counter = 0;
        }
    }
    if(counter > 0)
    {
        buffer[j++] = table[temp[0] >> 2];
        if(counter == 1) {
            buffer[j++] = table[(temp[0] & 0x03) << 4];
            buffer[j++] = pad;
        }
        else
        {
            buffer[j++] = table[((temp[0] & 0x03) << 4) + (temp[1] >> 4)];
            buffer[j++] = table[(temp[1] & 0x0f) << 2];
        }
        buffer[j++] = pad;
    }

    buffer[j] = '\0';
    return buffer;
}

char* base64_decode(char *plain)
{
    unsigned int size = (strlen(plain) * 3 / 4);
    char *buffer = (char *)malloc((size + 1) * sizeof(char));

    char temp[4];
    unsigned int i = 0, j = 0, k = 0, counter = 0;

    for(i = 0; plain[i] != '\0'; i++)
    {
        for(j = 0 ; j < 64 && table[j] != plain[i]; j++);
        temp[counter++] = j;
        if(counter == 4)
        {
            buffer[k++] = (temp[0] << 2) + (temp[1] >> 4);
            if(temp[2] != 64)
                buffer[k++] = (temp[1] << 4) + (temp[2] >> 2);
            if(temp[3] != 64)
                buffer[k++] = (temp[2] << 6) + temp[3];
            counter = 0;
        }
    }

    buffer[k] = '\0';
    return buffer;
}
