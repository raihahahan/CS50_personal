#include <stdio.h>
#include <stdlib.h>

int main(void) {

   typedef struct car
    {
        int year;
        char model[10];
        char plate[7];
        int odometer;
        double engine_size;
    }
    car_t;

    car_t f;

    typedef char* string;

    f.year = 2011;

    printf("%i\n", f.year);
}