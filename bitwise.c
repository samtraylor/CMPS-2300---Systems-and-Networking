#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <math.h>
  
void intToBinary(unsigned int num, int (*out)[32]) {
    int bits[32] = {0};
    for (int n = 31; n >= 0; n--) {
    	
    	int x = num >> n;

    	if (x & 1) {
    		(bits)[n] = 1;
    	}
    	
    	else {
    		(bits)[n] = 0;
    	}
    	
    }
    //reversing for right to left ordering
    int q = 0;
	for(int y = 31; y >= 0; y--) {
		(*out)[q] = bits[y];
		q++;
	}
}

int prefix(unsigned int x,unsigned int n) {

	int bits[32] = {0};
	int c = 0;
	int newArr[n];
	int decimal = 0;

	intToBinary(x,&bits);
	for(int b = 0; b < n; b++) {
		newArr[b] = bits[b];
	}
	
	for(int c; c < sizeof(newArr); c++) {
		decimal += pow(2,c);
	}
	return decimal;
}

int suffix(unsigned int x, unsigned int n) {
	return 0;
}
int toggle(unsigned int x,unsigned int n) {
	int bits[32] = {0};
	intToBinary(x,&bits);

	if(bits[(31-n)] == 1) {
		x &= ~(1 << n);
	}
	else if(bits[(31-n)] == 0) {
		x |= ~(1 << n);
	}
	return x; 
}

int main(void) {
	int bits[32] = {0};
	int afterToggle = toggle(5,2);
	intToBinary(afterToggle,&bits);
	printf("integer after bit toggled = %d.\n",afterToggle);
	printf("binary after bit toggled = ");
	for(int x = 0; x < 32; x++) {
		printf("%d",bits[x]);
	}
	printf("\n");

	int morebits[32] = {0};
	int pref= prefix(5,4);
	intToBinary(pref,&morebits);
	printf("decimal form of prefix = %d\n",pref);
	printf("binary of prefix = ");
	for(int p = 0; p < sizeof(morebits); p++) {
		printf("%d",morebits[p]);
	}

	return 0;
}