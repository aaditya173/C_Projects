#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char firstName[50];
    char lastName[50];
    int accountNumber;
    float balance;

} Account;

void showMenu();
void createAccount();
void depositeMoney();
void withdrawMoney();
void checkBalance();

int main()
{
    int choice;

    do
    {
        showMenu();
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            depositeMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            checkBalance();
            break;
        case 5:
            printf("Exiting\n");
            break;
        default:
            printf("Wrong Choice\n");
            break;
        }
    } while (choice != 5);

    return 0;
}

void showMenu()
{
    printf("+------------------------------------------+\n");
    printf("|     Welcome to Bank Management System    |\n");
    printf("+------------------------------------------+\n");
    printf("1. Create Account\n");
    printf("2. Deposite Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Check Balance\n");
    printf("5. Exit\n");
}
void createAccount()
{
    FILE *file = fopen("account.bin", "ab"); // Open for append in binary mode. Data is added to the end of the file. If the file does not exist, it will be created.
    // FILE *file = fopen("account.bin", "ab+"); // Open for both reading and appending in binary mode. If the file does not exist, it will be created.

    if (file == NULL)
    {
        printf("Error while Opening the file.!!\n");
        return;
    }

    char fName[50], lName[50];
    int accNo;
    Account *acc = (Account *)malloc(sizeof(Account));

    printf("Enter your First Name : ");
    scanf("%49s", fName);
    printf("Enter your Last Name : ");
    scanf("%49s", lName);
    printf("Enter your Account Number : ");
    scanf("%d", &accNo);
    printf("%s %s %d\n", fName, lName, accNo);
    strcpy(acc->firstName, fName);
    strcpy(acc->lastName, lName);
    acc->accountNumber = accNo;
    acc->balance = 0;

    fwrite(acc, sizeof(Account), 1, file);
    fclose(file);
    printf("Account Created Successfully.!!\n");
    return;
}
void depositeMoney()
{
    FILE *file = fopen("account.bin", "rb+"); // Open for both reading and writing in binary mode. If the file does not exist, fopen( ) returns NULL.

    if (file == NULL)
    {
        printf("Error while Opening the file.!!\n");
        return;
    }

    int accNo;
    float deposite;
    Account *acc = (Account *)malloc(sizeof(Account));

    printf("Enter your Account Number : ");
    scanf("%d", &accNo);
    printf("Enter amount to deposite : ");
    scanf("%f", &deposite);
    while (fread(acc, sizeof(Account), 1, file))
    {
        if (accNo == acc->accountNumber)
        {
            acc->balance += deposite;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(acc, sizeof(Account), 1, file);
            fclose(file);
            printf("You Deposidted %.2f Successfully in your Account.\nYour Current Account Balance is : %.2f\n", deposite, acc->balance);
            return;
        }
    }
    printf("Account Number : %d is not found.!!\n", accNo);
    fclose(file);
    return;
}
void withdrawMoney()
{
    int accNo;
    float withdraw;
    Account *acc = (Account *)malloc(sizeof(Account));
    FILE *file = fopen("account.bin", "rb+"); // Open for both reading and writing in binary mode. If the file does not exist, fopen( ) returns NULL.
    if (file == NULL)
    {
        printf("Error while Opening the file.!!\n");
        return;
    }
    printf("Enter your Account Number : ");
    scanf("%d", &accNo);
    printf("Enter amount to withdraw : ");
    scanf("%f", &withdraw);
    while (fread(acc, sizeof(Account), 1, file))
    {
        if (accNo == acc->accountNumber)
        {
            if (acc->balance > withdraw)
            {
                acc->balance -= withdraw;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(acc, sizeof(Account), 1, file);
                printf("You Withdrawal %.2f Successfully in your Account.\nYour Current Account Balance is : %.2f\n", withdraw, acc->balance);
            }
            else
            {
                printf("Insufficient Funds.!!\n");
            }
            fclose(file);
            return;
        }
    }
    printf("Account Number : %d is not found.!!\n", accNo);
    fclose(file);
    return;
}
void checkBalance()
{
    int accNo;
    Account *acc = (Account *)malloc(sizeof(Account));
    FILE *file = fopen("account.bin", "rb"); // Open for reading in binary mode. If the file does not exist, fopen( ) returns NULL.
    if (file == NULL)
    {
        printf("Error while Opening the file.!!\n");
        return;
    }
    printf("Enter your Account Number : ");
    scanf("%d", &accNo);
    while (fread(acc, sizeof(Account), 1, file))
    {
        if (accNo == acc->accountNumber)
        {
            printf("Your Current Account Balance is : %.2f\n", acc->balance);
            fclose(file);
            return;
        }
    }
    printf("Account Number : %d is not found.!!\n", accNo);
    fclose(file);
    return;
}