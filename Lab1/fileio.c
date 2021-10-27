#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Program to generate performance statistics based on user-defined idle time over a specified amount of days

@author Sam Traylor
@version 1.0
*/

int main(int argc, char *argv[]) {
	char characters[100];
	char morechars[100];
	int array[10000];
	int y; 
	int day = 0; 
	int count = 0;
	int totalIdle = 0;
	int lowestLoad = 0;
	int highestLoad;
	double rate = 0.0;

	FILE* wiTuLo = fopen(argv[1], "r");
	FILE* fileout;
	fgets(characters, sizeof(characters), wiTuLo);
	printf("%s", characters);
	
	while(fgets(morechars, sizeof(morechars), wiTuLo)!= NULL) {
		count++;
		array[day] = atoi(morechars);
		y = atoi(morechars);
		printf("%d\n", y);
		day++;

		if(count == 1) {
			highestLoad = 0;
			lowestLoad = 1234567;
		}
		if(highestLoad < y) {
			highestLoad = day;
		}
		if(lowestLoad > y) {
			lowestLoad = day;
		}
		totalIdle += y;
	}

	fclose(wiTuLo);
	double totaltwo = totalIdle;
	int mins = count * 1440;
	rate = totaltwo / mins;
	double averageIdle = totaltwo / count; 
	
	printf("Total idle time is: %d minutes.\n", totalIdle);
	printf("Amount of week spent idling: %f percent.\n", (totaltwo / mins));
	printf("Average daily idle time: %f minutes.\n", (totalIdle / 7.0));
	printf("Day with lowest load: day %d. \n Day with highest Load: day %d.", lowestLoad + 1, highestLoad + 1);

	fileout = fopen(argv[2], "w");

	fprintf(fileout, "Total: %d\n", totalIdle);
	fprintf(fileout, "Average: %f\n", averageIdle);
	fprintf(fileout, "Performance Rate: %f\n", rate);
	fprintf(fileout, "highest Day: %d\n", highestLoad);
	fprintf(fileout, "lowest Day: %d\n", lowestLoad);

	return 0;
}