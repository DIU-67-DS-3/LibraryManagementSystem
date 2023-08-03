/*
    Author: S M Moshaddaque Hoshain
*/

#include<stdio.h>

void addBooks()
{

}

typedef struct car {
    char name[50];
    char engine[20];
    int seating_cap;
} car;



int main()
{
    car c1;
    c1 = {"tesla", "strong", 8};

    printf("%s %s %d", c1.name, c1.engine, c1.seating_cap);

    return 0;
}

