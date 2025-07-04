#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void printTime();
void printDate();
void clearScreen();

int main()
{
    while (1)
    {
        clearScreen();
        printTime();
        printDate();
        Sleep(1000);
    }
    

    return 0;
}

void printTime()
{
    time_t rawTime;
    struct tm *currentTime;
    char buffer[50];

    time(&rawTime);
    currentTime = localtime(&rawTime);
    strftime(buffer, sizeof(buffer), "%I:%M:%S %p", currentTime);
    printf("%s\n", buffer);
}

void printDate(){
    time_t rawDate;
    struct tm *currentDate;
    char buffer[50];

    time(&rawDate);
    currentDate = localtime(&rawDate);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %A", currentDate);
    printf("%s\n", buffer);
}

void clearScreen() {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #elif defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}