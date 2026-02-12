#include <stdio.h>
#include "main.h"

//void add(int a, int b);  // Function prototype


int main() {

    //printf("Sum: %d\n", add(3, 4));
    add(5, 7);
    //printf("Hello, World!\n");
    // short num = 65534;
    // printf("Short: %d\n", num);

    // int largeNum = 2147483647;
    // printf("Int: %d\n", sizeof(largeNum));

    // long veryLargeNum = 9223372036854775807;
    // printf("Long: %d\n", sizeof(veryLargeNum));

    // long long hugeNum = 9223372036854775807;
    // printf("Long Long: %d\n", sizeof(hugeNum));
    //char
    // char letter = 'A';
    // printf("Char: %d\n", sizeof(letter));
    // printf("Char value: %c\n", letter);
    // printf("Char ASCII: %d\n", letter);
    // char anotherLetter = 66; 
    // printf("Another Char value: %c\n", anotherLetter);

    // float vs double
    // float num = 3.14;
    // double bigNum = 2.718281828;
    // printf("Float: %d\n", sizeof(num));
    // printf("Double: %d\n", sizeof(bigNum));


    // float array[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    // float thirdElement = array[2];
    // printf("Third element: %.1f\n", thirdElement);
    // array[2] = 9.9;
    // printf("Updated third element: %.1f\n", array[2]);
    // if (5 < 10 && 2 > 3) {
    //     printf("This will always print.\n");
    // } else {
    //     printf("This will never print.\n");
    // }

    // char age = 'o';
    // switch (age) {
    //     case 'A':
    //         printf("You are 18 years old.\n");
    //         break;
    //     case 'B':
    //         printf("You are 25 years old.\n");
    //         break;
    //     default:
    //         printf("Age not matched.\n");
    // }

    // int number = 10;

    // if (number++ > 10) {
    //     printf("Number is positive.\n");
    // } 

    // int count = 0;
    // while (count < 5) {
    //     printf("Count: %d\n", count);
    //     count++;
    // }

    // do
    // {
    //     printf("This will run at least once.\n");
    // } while (0);
    // while (0)
    // { 
    //     printf("This will not run.\n");
    // }

    
    // for (int i = 0; i < 5; i++) {
    //     printf("Iteration: %d\n", i);
    // }

    return 0;
}


void add(int a, int b) {
    printf("Sum: %d\n", a + b);
}