#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <unistd.h>


int main() {

    int lenght = 16;
    char *password = malloc(lenght + 1);

    char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *lower = "abcdefghijklmnopqrstuvwxyz";
    char *num = "0123456789";
    char *symbol = "<>,.?/;:'[]{}()!@#$%^&*";
    
    int upper_lenght = strlen(upper);
    int lower_lenght = strlen(lower);
    int num_lenght = strlen(num);
    int symbol_lenght = strlen(symbol);

    srand(trime(NULL) * getpid());

    for (int i = 0; i < lenght; i++){
        int c_type = rand() % 4;

        if (c_type == 0)
            password[i] = num[rand() % num_lenght];

        else if (c_type == 1)
            password[i] = lower[rand() % lower_lenght];

        else if (c_type == 2)
            password[i] = upper[rand() % upper_lenght];

        else
            password[i] = symbol[rand() % symbol_lenght];

        password[lenght] = '\0';

        printf("%s\n", password);
        free(password);


        return 0;

    }
}