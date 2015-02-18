#include <stdio.h>
#include <stdlib.h>

typedef struct _list
{
	int data;
	struct _list *next;
} list;


list* make_node(int value);
void add_end(list **List, int data);
void display(list *List);

int main()
{
	list *List = NULL;

	add_end(&List, 10);
	add_end(&List, 20);
	add_end(&List, 30);
	add_end(&List, 40);
	display(List);

	return 0;
}

list* make_node(int value)
{
	list *newnode = malloc(sizeof(list));
	if (newnode == NULL) {
		printf("Error:malloc failed.\n");
		return (list*)-1;
	}
	newnode->data = value;
	newnode->next = newnode;
	return newnode;	
}

void add_end(list **List, int data)
{
	list *head, *temp, *newnode;
	head = *List;
	temp = *List;

	newnode = make_node(data);
	if(temp == NULL) {
		*List = newnode;
		return;
	}

	while (temp->next != head)
		temp = temp->next;
	temp->next = newnode;
	newnode->next = head;	
}

void display(list *List)
{
	list *head = List;
		
	if (List == NULL) {
		printf("List is empty.\n");
		return;
	}
	printf("List data :: ");
	do {
		printf("%d ", List->data);
		List = List->next;	
	} while (List != head);
	printf("\n");
}
