/*
@author Sam Traylor 
@version 1.0

Class for a c linked list implimentation
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
The * and & operators are for using pointers. 
Declaring a variable as int* instead of int, for example,
would mean that it stores a pointer object instead of a literal 
value. The 'pointer' object is called such because it points to
a specific address in memory, where the actual value of a variable 
is stored. The & symbol is used to return an address of a variable,
meaning if you prepend it to a var, (&userNum, for example) it will 
return a pointer to the variable instead of it's data.
*/

typedef struct Node_struct {
	int data;
	struct Node_struct* next;
} Node;

void add(Node ** head, int data) {
	Node* pushed;
	pushed = malloc(sizeof(Node));

	pushed->data = data;
	pushed->next = *head;
	*head = pushed;
}

void removeNode(Node ** head) {
    Node * next_node;
    next_node = (*head)->next;

    free(*head);
    *head = next_node;
}

int main(void) {
	Node * head = NULL;
	head = malloc(sizeof(Node));
	
	head->data = 1;
	head->next = NULL;

	head->next = malloc(sizeof(Node));
	head->next->data = 2;
	head->next->next = NULL;

	printf("%d %d\n", head->data, head->next->data);

    int tdata = 6;
    add(&head, tdata);

    printf("%d %d %d \n", head->data, head->next->data, head->next->next->data);

    removeNode(&head);
    removeNode(&head); 

    printf("%d \n", head->data);
}

