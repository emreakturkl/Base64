#include <stdio.h>
#include <stdlib.h>
#include "base64.h"

#define PLAIN_TEXT "HELLO WORLD"

int main()
{
    char *en = base64_encode(PLAIN_TEXT);
    char *de = base64_decode(en);

    printf("Plain Text   : %s\n", PLAIN_TEXT);
    printf("Base64 Encode: %s\n", en);
    printf("Base64 Decode: %s\n", de);

    return 0;
}
