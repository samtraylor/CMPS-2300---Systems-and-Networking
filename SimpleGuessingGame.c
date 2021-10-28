/*
@author Sam Traylor 
@version 1.0

Class used to play a guessing game, where user must guess numbers until 
they enter the num inside specified range.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Method used for taking user input and determining whether in specified 
range. If not specified, user will enter numbers until one in range, which 
is returned.

@param min minimum of specified range 
@param max maximum of specified range
@return integer that was found to be in range
*/

int ask_in_range(min,max) {
	int userNum = 0;
	
	printf("Please enter a number: ");
	scanf("%d",&userNum);

	while(userNum < min || userNum > max) {
		printf("Your number is outside of [%d, %d] range. Please enter a number: ", min, max);
		scanf("%d",&userNum);
	}

	if(userNum >= min && userNum <= max){
		return userNum;
	}
	
}

int guessing_game(num, rangemin, rangemax) {

	int guessNum = 0;

	printf("Hello and welcome to the game.\n");
	printf("You need to guess a number between %d and %d.\n", rangemin,rangemax);

	while(1) {
	int number = ask_in_range(rangemin,rangemax);
    guessNum++;

		if(number == num) {
			break;
		}

		if(number < num) {
			printf("Too low!\n");

		}

		if(number > num) {
			printf("Too high!\n");
		}
	}
	printf("Good job! You took %d guesses.\n", guessNum);

}