#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void register_user();
int login_user();
void fix_fgets_input(char *);
void getPassword(char *password);
void input_credentials(char *username, char *password);

int main()
{
    int option;
    int user_index;

    do
    {
        printf("Welcome to User Management\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:
            register_user();
            break;
        case 2:
            user_index = login_user();
            if (user_index >= 0)
            {
                printf("Login successful! Welcome, %s!\n", users[user_index].username);
            }
            else
            {
                printf("Login failed! Incorrect username or password.\n");
            }
            break;
        case 3:
            printf("Exiting Program.\n");
            return 0;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    } while (option != 3);

    return 0;
}

void register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("Maxximum %d users are supported! No more registrations Allowed!!!!\n", MAX_USERS);
        return;
    }

    int new_index = user_count;
    printf("Register a new user");
    input_credentials(users[new_index].username, users[new_index].password);

    user_count++;
    // printf("-%s-%s-", users[new_index].username, users[new_index].password);
    printf("Registration successful!\n");
}
int login_user()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    input_credentials(username, password);

    for (int i = 0; i < MAX_USERS; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            // printf("-%s-%s-", username, password);
            return i;
        }
    }
    return -1;
}
void fix_fgets_input(char *str)
{
    int index = strcspn(str, "\n");
    str[index] = '\0';
}
void getPassword(char *password)
{
    int i = 0;
    char ch;

#ifdef _WIN32
    while ((ch = _getch()) != '\r' && i < CREDENTIAL_LENGTH - 1)
    {
        if (ch == '\b')
        {
            if (i > 0)
            {
                printf("\b \b");
                fflush(stdout);
                i--;
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n' && i < CREDENTIAL_LENGTH - 1)
    {
        if (ch == 127 || ch == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    password[i] = '\0';
    printf("\n");
}
void input_credentials(char *username, char *password)
{
    printf("Enter Username : ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);
    printf("Enter you password (making enable): ");
    getPassword(password);
}