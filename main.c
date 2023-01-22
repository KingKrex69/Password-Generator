#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *res = malloc(17), 
               *listing = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234567890123456789";

    srand((unsigned int)time(NULL));

    for(int i = 0; i < 16; ++i)
        res[i] = listing[rand() % 73];

    res[16] = '\0';

    puts(res);
    free(res);
}
