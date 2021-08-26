#include <stdio.h>

int main () {
    int var = 20;
    int *ip = NULL;
    ip = &var;

   printf("Address of var variable: %p\n", ip);

   return 0;
}