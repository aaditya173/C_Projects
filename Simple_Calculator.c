#include<stdio.h>
#include<math.h>

void showMenu();
void switchConditions(int);
void addition();
void substraction();
void multiplication();
void division();
void modulus();
void power();

int main(){
    int choice;
    
    do{
        showMenu();

        printf("Enter your choice : ");
        scanf("%d", &choice);

        switchConditions(choice);

    }while(choice != 7);

    printf("Thanks for Using this calculator.\n");
    printf("Devloped by Aditya Kasaudhan\n");
    
    return 0;
}

void showMenu(){
    printf("\n+-------------------------------------+\n");
    printf("|    Welcome to Simple Calculator     |");
    printf("\n+-------------------------------------+\n");
    // printf("-----------------------------------------------\n");
    printf("Choose one of the following options:\n");
    printf("1. Addition\n");
    printf("2. Substraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("6. Power\n");
    printf("7. Exit\n");
}
void switchConditions(int choice){
    switch (choice){
        case 1: // Addition
            addition();
            break;
        case 2: // Substraction
            substraction();
            break;
        case 3: // Multiplication
            multiplication();
            break;
        case 4: // Division
            division();
            break;
        case 5: // Modulus
            modulus();
            break;
        case 6: // Power
            power();
            break;
        case 7: // Exit
            printf("Exit!!\n");
            break;
        default: // Default Case
            printf("Wrong Choice !!\n");
            break;
    }
}
void addition(){
    double firstNumber, secondNumber, result;
    printf("Enter the first number : ");
    scanf("%lf", &firstNumber);
    printf("Enter the second number : ");
    scanf("%lf", &secondNumber);
    result = firstNumber + secondNumber;
    printf("The result is : %.2f\n", result);
}
void substraction(){
    double firstNumber, secondNumber, result;
    printf("Enter the first number : ");
    scanf("%lf", &firstNumber);
    printf("Enter the second number : ");
    scanf("%lf", &secondNumber);
    result = firstNumber - secondNumber;
    printf("The result is : %.2f\n", result);
}
void multiplication(){
    double firstNumber, secondNumber, result;
    printf("Enter the first number : ");
    scanf("%lf", &firstNumber);
    printf("Enter the second number : ");
    scanf("%lf", &secondNumber);
    result = firstNumber * secondNumber;
    printf("The result is : %.2f\n", result);
}
void division(){
    double firstNumber, secondNumber, result;
    printf("Enter the first number : ");
    scanf("%lf", &firstNumber);
    printf("Enter the second number : ");
    scanf("%lf", &secondNumber);
    if(secondNumber == 0){
        printf("Second Number should not be 0.\n");
        return;
    }
    result = firstNumber / secondNumber;
    printf("The result is : %.2f\n", result);
}
void modulus(){
    int firstNumber, secondNumber, result;
    printf("Enter the first number : ");
    scanf("%d", &firstNumber);
    printf("Enter the second number : ");
    scanf("%d", &secondNumber);
    if(secondNumber == 0){
        printf("Second Number should not be 0.\n");
        return;
    }
    result = firstNumber % secondNumber;
    printf("The result is : %d\n", result);
}
void power(){
    double firstNumber, secondNumber, result;
    printf("Enter the first number : ");
    scanf("%lf", &firstNumber);
    printf("Enter the second number : ");
    scanf("%lf", &secondNumber);
    result = pow(firstNumber, secondNumber);
    printf("The result is : %.2f\n", result);
}