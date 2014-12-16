/* Double linked list implementation for learning purpose
 * By sujin
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define OP_START    0
#define OP_MIDDLE   1
#define OP_END      2


typedef struct _llist
{
    int data;
    struct _llist *prev;
    struct _llist *next;
}llist;

/* function prototype declaration */
llist* make_node(int data);
void add_end(llist **List, int data);
void display_list(llist *);
void add_front(llist **List, int data);
void add_middle(llist **List, int data, int after);

int main(int argc, char *argv[])
{
    llist *List = NULL;
    add_end(&List, 10);
    add_end(&List, 20);
    add_end(&List, 30);
    add_end(&List, 40);
    display_list(List);
    
    add_front(&List, 21);
    add_front(&List, 31);
    add_front(&List, 41);
    add_end(&List, 50);
    add_end(&List, 60);
    display_list(List);
    
    add_middle(&List, 29, 30);
    display_list(List);
    
    add_middle(&List, 39, 41);
    display_list(List);
    
    add_middle(&List, 49, 60);
    display_list(List);
    
    add_middle(&List, 599, 3000);
    display_list(List);
    
    return 0;
}

void add_list(list **List)

llist* make_node(int data)
{
    llist *newnode = malloc(sizeof(llist));
    if (newnode == NULL)
    {
        printf("ERROR : malloc failed\n");
        exit(-1);
    }
    newnode->prev = NULL;
    newnode->next = NULL;
    newnode->data = data;
    
    return newnode;
}

void add_middle(llist **List, int data, int after)
{
    llist *temp, *newnode;
    newnode = make_node(data);
    temp = *List;
    if (temp == NULL) {
        *List = newnode;
        return;
    }
    
    while (temp->data != after && temp->next != NULL)
        temp = temp->next;
    if (temp->data == after && temp->next != NULL) {
        newnode->prev = temp;
        newnode->next = temp->next;
        temp->next->prev = newnode;
        temp->next = newnode;
    }
    else {
        if (temp->data != after)
            printf("Position %d not found in the list, since insert at the end...\n", after);
        temp->next = newnode;
        newnode->prev = temp;
    }
}

void add_front(llist **List, int data)
{
    llist *temp, *newnode;
    newnode = make_node(data);
    temp = *List;
    if (temp == NULL) {
        *List = newnode;
        return;
    }
    newnode -> next = temp;
    temp -> prev = newnode;
    *List = newnode;
}

void add_end(llist **List, int data)
{
    
	llist *temp, *newnode;
	newnode = make_node(data);
	temp = *List;
	if (temp == NULL) {
	    *List = newnode;
	    return;
	}
    
    while (temp->next != NULL) {
        temp = temp -> next;
    }
    newnode -> prev = temp;
    temp -> next = newnode;
}

void display_list(llist *List)
{
    printf("Elements from the list are :: ");
    while (List) {
        printf("%d <--> ", List -> data);
        List = List -> next;
    }
    printf("NULL\n\n");
}
    
