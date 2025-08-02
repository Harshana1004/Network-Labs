// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:
node* createnode(char* word) {
	node* newnode = malloc(sizeof(node));
    if (!newnode) return NULL;

    newnode->word = malloc(strlen(word) + 1);
    if (!newnode->word) {
        free(newnode);
        return NULL;
    }

    strcpy(newnode->word, word);
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

node* getnode(list* lst,int index){
	if (!lst || !lst->head) return NULL;
	node* current = lst->head;
	if (index == 0) return current;

	if (index>0){
		for (int i=0;i<index;i++){
			current = current->next;
		}
	}
	else {
		for (int i=0;i>index;i--){
			current = current->prev;
		}
	}
	return current;
}

// implementation
void insert_node_before(list *lst, int index, char *word)
{	
	// TODO
	node* newnode = createnode(word);
	if (!newnode) return;

	if (!lst->head){
		lst->head = newnode;
		newnode->next = newnode->prev = newnode;
		return;
	}

	node* currentnode = getnode(lst,index);
	if (!currentnode) {
		free(newnode);
		return;
	}

	newnode->next = currentnode;
	newnode->prev = currentnode->prev;
	currentnode->prev->next = newnode;
	currentnode->prev = newnode;

	
}

void insert_node_after(list *lst, int index, char *word)
{
	// TODO
	node* newnode = createnode(word);
	if (!newnode) return;
	if (!lst->head) {
		lst->head = newnode;
		newnode->next = newnode->prev = newnode;
		return;
	}

	insert_node_before(lst,index+1,word);

}

char *list_to_sentence(list *lst)
{
	// TODO
	if (!lst || !lst->head) {

        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    int total_length = 0;
    int word_count = 0;
    node *current = lst->head;

    do {
        total_length += strlen(current->word);
        word_count++;
        current = current->next;
    } while (current != lst->head);

    total_length += word_count - 1;
    total_length += 1;  

    char *sentence = malloc(total_length);
    if (!sentence) return NULL;
    sentence[0] = '\0';

    current = lst->head;
    for (int i = 0; i < word_count; i++) {
        strcat(sentence, current->word);
        if (i < word_count - 1) strcat(sentence, " ");
        current = current->next;
    }

    return sentence;
    
     
}

void delete_node(list *lst, int index)
{
	// TODO
	if (!lst || !lst->head) return;

	node* currentnode = getnode(lst,index);
	if (!currentnode) return;
	if (currentnode->next == currentnode){
		free(currentnode);
		lst->head = NULL;
		return;
	}
	currentnode->prev->next = currentnode->next;
	currentnode->next->prev = currentnode->prev;
	if (currentnode == lst->head){
		lst->head = currentnode->next;
	}
	free(currentnode);

}

void delete_list(list *lst)
{
	// TODO
	if (!lst || !lst->head) return;

    node* currentnode = lst->head;

    while (currentnode) {
        node* next = currentnode->next;
        free(currentnode->word);
        free(currentnode);
        currentnode = next;
    } 

    lst->head = NULL;
}
