#include <stdlib.h>
#include <stdio.h> 
  
void intToBinary(unsigned int num, int (*out)[32]) {
    for (int n = 31; n >= 0; n--) {
    	
    	int x = num >> n;

    	if (x & 1) {
    		(*out)[n] = 1;
    	}
    	
    	else {
    		(*out)[n] = 0;
    	}
    	
    }
    printf("done translating\n");
	//printf("%d",*out);
	
}

int prefix(unsigned int x,unsigned int n) {
	return 0;
}
int suffix(unsigned int x, unsigned int n) {
	return 0;
}
int toggle(unsigned int x,unsigned int n) {
	return 0;
}

int main(void) {
	int bits[32] = {0};
	int test = 5;
	intToBinary(test,&bits);
	for(int y = 0; y < 32; y++) {
		printf("%d",(bits)[y]);
	}
    printf("\n");
	return 0;
}