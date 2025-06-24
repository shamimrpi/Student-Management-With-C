#include <stdio.h>
#include <stdlib.h>

// Function to check prime number
int isPrime(int number) {
    if (number <= 1) return 0;
    for (int i = 2; i <= number / 2; i++) {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

// Function to check leap year
int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    else
        return 0;
}

int main() {
    int choice;
    int number, year;

    while (1) {
        printf("\n===== Menu =====\n");
        printf("1. Check Prime Number\n");
        printf("2. Check Leap Year\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to check if it is prime: ");
                scanf("%d", &number);
                if (isPrime(number))
                    printf("%d is a Prime Number.\n", number);
                else
                    printf("%d is NOT a Prime Number.\n", number);
                break;

            case 2:
                printf("Enter a year to check if it is a leap year: ");
                scanf("%d", &year);
                if (isLeapYear(year))
                    printf("%d is a Leap Year.\n", year);
                else
                    printf("%d is NOT a Leap Year.\n", year);
                break;

            case 3:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice. Please select between 1 and 3.\n");
        }
    }

    return 0;
}
