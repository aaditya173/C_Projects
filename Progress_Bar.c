#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define BAR_LENGTH 50
#define MAX_TASKS 5

typedef struct{
    int taskNumber;
    int progress;
    int steps;
} Task;

void clearScreen();
void printProgress(Task);

int main(){
    srand(time(NULL));
    Task * tasks = (Task *)malloc(sizeof(Task) * MAX_TASKS);
    if(tasks == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for(int i=0; i<MAX_TASKS; i++){
        tasks[i].taskNumber = i+1;
        tasks[i].progress  = 0;
        // tasks[i].progress  = rand() % 100 + 1; // for generating random progress
        tasks[i].steps = rand() % 5 +1;
    }

    int tasksNotCompleted = 1;
    while(tasksNotCompleted){
        clearScreen();
        tasksNotCompleted = 0;
        for(int i=0; i<MAX_TASKS; i++){
            tasks[i].progress = tasks[i].progress + tasks[i].steps;
            if(tasks[i].progress > 100){
                tasks[i].progress = 100;
            }
            if(tasks[i].progress < 100){
                tasksNotCompleted = 1;
            }
            printProgress(tasks[i]);
        }
        Sleep(1000);
    }
    printf("All Tasks Completed!!");


    return 0;
}

void clearScreen() {
    // printf("\033[2J\033[H"); // ANSI escape code: clear screen and move cursor to home position
    // system("cls"); // for windows but not working properly
    // system("clear"); // for linux and mac and also working on my pc
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #elif defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}


void printProgress(Task t){
    int taskNumber = t.taskNumber;
    int progress = t.progress;
    int bar_filled = (progress*BAR_LENGTH) / 100;
    printf("Task %d : [", taskNumber);
    fflush(stdout);
    for(int i=1; i<BAR_LENGTH; i++){
        if(i<bar_filled){
            printf("=");
        }
        else if(i == bar_filled){
            printf(">");
        }
        else{
            printf(" ");
        }
        fflush(stdout);
    }
    printf("] %d%%\n", progress);
}