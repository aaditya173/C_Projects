#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int randomNumber, guessedNumber;
    int no_of_guesses = 0;
    srand(time(NULL));

    printf("Welcome to the world of Number Guessing Game.\n");

    randomNumber = rand()%100+1; //Generating Numbers between 1 to 100

    do{
        printf("Please enter your Guess (1-100) : ");
        scanf("%d", &guessedNumber);

        no_of_guesses++; // for ccounting the number of guesses

        if(guessedNumber < randomNumber){
            printf("Guess Larger Numbers.\n");
        }else if(guessedNumber > randomNumber){
            printf("Guess Smaller Numbers.\n");
        }else{
            printf("Congratulations ##You successfully guessed the number in %d attemps.##\n", no_of_guesses);
        }

    }while(guessedNumber != randomNumber);

    printf("Thanks for Playing the game.\n");
    printf("Devloped by Aditya Kasaudhan\n");

    return 0;
}