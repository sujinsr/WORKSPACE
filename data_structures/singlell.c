/* Single linked list implementation for learning purpose.
 * By Sujn
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define OP_START		0
#define OP_MIDDLE 		1
#define OP_END 		    2

typedef struct _list
{
	int data;
	struct _list *next;
}list;


void add_end(list **List, int value);
void add_start(list **List, int value);
void add_middle(list **List, int value, int after);
list* make_node(int value);
void add_list(int num, ...);
void delete_node(list **List, int value);
void countNode(list *List);
void displayNode(list *List);
void deleteAllnode(list **List);

int main()
{
	list *List = NULL;
	int i = 0;

	for (i = 0; i < 5; i++)
		add_list(3, &List, OP_END, (i+1)*10);
	countNode(List);
	displayNode(List);

	add_list(3, &List, OP_START, 25);
	add_list(3, &List, OP_START, 45);
	countNode(List);
	displayNode(List);

	add_list(4, &List, OP_MIDDLE, 32, 30);
	add_list(4, &List, OP_MIDDLE, 42, 45);
	add_list(4, &List, OP_MIDDLE, 52, 11);
	add_list(4, &List, OP_MIDDLE, 72, 52);
	countNode(List);
	displayNode(List);
	
	delete_node(&List, 40);
	deleteAllnode(&List);
	countNode(List);
	//`displayNode(List);

	/*add_list(3, &List, OP_END, 1000);
	add_list(4, &List, OP_MIDDLE, 5555, 42);
	add_list(3, &List, OP_START, 1111222);
	countNode(List);
	displayNode(List);*/

	return 0;
}

void deleteAllnode(list **List)
{
	list *temp = *List, *delnode;

	while (temp != NULL) {
		delnode = temp;
		temp = temp -> next;	
		free(delnode);
		delnode = NULL;
	}
	*List = NULL;
}

list* make_node(int value)
{
	list *newnode = malloc (sizeof(list));
	if (newnode == NULL)
		printf("malloc failed\n");
	else {
		newnode -> data = value;
		newnode -> next = NULL;
	}
	return newnode;	
}

void add_list(int num, ...)
{
	va_list valist;
	list **List;
	int opt, data, pos = 0;

	va_start(valist, num);
	List = va_arg(valist, list**);
	opt = va_arg(valist, int);
	data = va_arg(valist, int);
	pos = va_arg(valist, int);

	if (opt == OP_START)
		add_start(List, data);
	else if(opt == OP_MIDDLE)
		add_middle(List, data, pos);
	else
		add_end(List, data);
	va_end(valist);
}

void add_end(list **List, int value)
{
	list *temp, *newnode;

	newnode = make_node(value);

	if (*List == NULL) {
		*List = newnode;
		return ;
	}
	temp = *List;

	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = newnode;
}

void add_start(list **List, int value)
{
	list *newnode, *temp;
	
	temp = *List;

	newnode = malloc(sizeof(list));
	newnode->data = value;
	newnode->next = NULL;

	if (temp == NULL) {
		*List = newnode;
		return ;
	}

	newnode -> next = temp;
	*List = newnode;
	
	return;
}

void add_middle(list **List, int value, int after)
{
	list *temp, *temp1, *newnode;
	temp = *List;
	
	newnode = malloc(sizeof(list));
	newnode -> data = value;
	newnode -> next = NULL;

	if (temp == NULL) {
		*List = newnode;
		return;
	}
	
	while ((temp -> data != after) && (temp -> next != NULL))
		temp = temp -> next;

	if (temp -> data != after) {
		printf("Givent postion not available, so inserting at end of the list...\n");
		temp -> next = newnode;
	}
	else {
		temp1 = temp -> next;
		temp -> next = newnode;
		newnode -> next = temp1;
	}
	return;

}

void delete_node(list **List, int value)
{
	list*temp, *temp1, *delnode;
	temp = *List;
	if (temp == NULL) {
		printf("Empty List...\n");
		return ;
	}
	
	if (temp -> data == value) {
		delnode = temp;
		*List = temp -> next;
		free(delnode);
		return ;
	}

	temp1 = temp->next;
	while ((temp1 -> data != value) && (temp1 !=NULL)) {
		temp = temp -> next;
		temp1 = temp -> next;
	}
	
	if (temp1 -> data == value) {
		delnode = temp1;
		temp -> next = temp1->next;
		free(delnode);
	}
	else
		printf("Node not found...\n");

	return;
}

void displayNode(list *List)
{
	printf("List elements are :");
	while (List != NULL) {
		printf(" %d", List -> data);
		List = List -> next;
	}
	printf("\n\n");
}

void countNode(list *List)
{
	int count = 0;
	while (List != NULL) {
		count ++;
		List = List -> next;
	}
	printf("Number of node in list : [ %d ]\n", count);
}
