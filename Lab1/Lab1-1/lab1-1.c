// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "node.h"


// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst); 
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) 
{
    char buffer[500];

    // Read first line (initial comma-separated words)
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
        char *token = strtok(buffer, ",");
        while (token != NULL) {
            insert_node_after(lst, -1, token); // insert at end
            token = strtok(NULL, ",");
        }
    }

    // Now read and process operations
    int opcode, index;
    char word[100];

    while (scanf("%d", &opcode) == 1 && opcode != 0) {
        if (opcode == INSERT_BEFORE || opcode == INSERT_AFTER) {
            scanf("%d %s", &index, word);
            if (opcode == INSERT_BEFORE)
                insert_node_before(lst, index, word);
            else
                insert_node_after(lst, index, word);
        } else if (opcode == DELETE_NODE) {
            scanf("%d", &index);
            delete_node(lst, index);
        }
    }
	
}

//Print the list contents
void print_list(list * lst)
{
    char* sentence = list_to_sentence(lst);
    printf("%s\n",sentence);
    free(sentence);
   
}

