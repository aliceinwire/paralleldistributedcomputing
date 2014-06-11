#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};

static struct node *head;

void revlist(struct node **head)
{
	struct node *prev, *curr, *next;

	if (!*head)
		return; 
	curr = *head;
	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

void printlist(struct node *head)
{
	struct node *temp = head;

	temp = head;
	printf("\nThe list looks like...\n");
	while (temp) {
		printf("%d...", temp->value);
		temp = temp->next;
	}
	printf("End of list.\n");
} 

void add_value(int value)
{
	struct node *newnode = (struct node *) malloc(sizeof(struct node));
	struct node *temp;

	if (!newnode) {
		printf("I cannot allocate more memory, giving up\n");
		// cleanup the list
		exit (-1);
	} 
	newnode->next = NULL;
	newnode->value = value;
	if (!head)
		head = newnode;
	else {
		temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	} 
}

void take_user_input()
{
	int count = 0, value;

	printf("How long a linked list do you want to create?\n");
	scanf("%d", &count);
	while (count--) {
		printf("Enter value (%d more remaining): ", count);
		scanf("%d", &value);
		add_value(value);
	}
}

int main(int argc, char **argv)
{
	printf("This program creates a linked list with data input by you and" \
		" will reverse it in single traversal\n");
	take_user_input();
	printf("Original list...");
	printlist(head);
	revlist(&head);
	printf("Reversed list...");
	printlist(head); 
	return 0;
}

