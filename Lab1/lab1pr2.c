#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
Program to verify whether given sequence of numbers is a valid hexidecimal number.

@author Sam Traylor 
@version 1.0
*/

bool isHex(char *st) {
	bool hex = true;

	for(int x = 0; x < strlen(st); x++) {
		if(('A' <= st[x] && st[x] <= 'F') || ('0' <= st[x] && st[x] <= '9')) {
			hex = true;
		}
		else {
			hex = false;
			return false;
		}
	}
	return true;
}

int main(void) {
	char *string;
	bool hex = false;

	printf("Please enter a hexidecimal sequence, then press enter, then 'c' for confirm, then enter once more: \n");
	scanf("%s\n", string);

	while(hex == false) {
		if(isHex(string) == 1) {
			printf("Thank you!");
			hex = true;
			return hex;
		}
		else {
			printf("Please enter a hexidecimal sequence, then press enter, then 'c' for confirm, then enter once more: \n");
			scanf("%s\n", string);
		}
	}
}