/*
@author Sam Traylor 
@version 1.0

Class used to play a guessing game, where user must guess numbers until 
they enter the randomly generated num inside specified range.
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

int get_random(rangemin,rangemax) {
	srand(time(0));
	int random = rand() % (rangemax - rangemin + 1) + rangemin;
	return random;
}
//It takes a maximum of 500 guesses to find a # within range [-500,500]

int guessing_game(rangemin, rangemax) {

	int num = get_random(rangemin,rangemax);
	int guessNum = 0;
	char name[50];

	printf("Hello and welcome to the game.\n");
	printf("Please enter your first name: \n");
	scanf("%s", name); 
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

	char prevName[50];
	int prevScr = 0;
	FILE* f = fopen("history.txt","r");

	while(!feof(f)) {
		if(fscanf(f, "%s", prevName) == 1) {
			fscanf(f, "%d", &prevScr);
		}
	} 
	printf("Previous user: %s \nTheir score: %d\n", prevName, prevScr);
	fclose(f);

	FILE* f2 = fopen("history.txt", "w");
	fprintf(f2, "%s -- %d", name, guessNum);
	fclose(f2);
}
