// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.h"

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

// parse the input
void run(chain *chn) 
{
    int n;
    scanf("%d", &n);
    if (n <= 0) return;

    int** rows = malloc(n * sizeof(int *));
    if (!rows) return;
    int cols = -1;

    char buffer[1024];
    getchar(); 

    for (int i = 0; i < n; i++) {
        rows[i] = malloc(100 * sizeof(int));
        if (!rows[i]) {
           
            for (int k = 0; k < i; k++) free(rows[k]);
            free(rows);
            return;
        }

        if (!fgets(buffer, sizeof(buffer), stdin)) {
           
            for (int k = 0; k <= i; k++) free(rows[k]);
            free(rows);
            return;
        }

        int count = 0;
        char* token = strtok(buffer, " \t\n");
        while (token && count < 100) {
            rows[i][count++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }
        if (cols == -1) cols = count;
    }

    matrix* mat = create_matrix(n, cols);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < cols; j++) {
            mat->data[i][j] = rows[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        free(rows[i]);
    }
    free(rows);

   
    node* new_node = malloc(sizeof(node));
    if (!new_node) {
        delete_matrix(mat);
        return;
    }
    new_node->mat = mat;
    new_node->next = new_node;
    new_node->prev = new_node;
    chn->head = new_node;

    print_matrix(mat);
    printf("\n");


    int code;
    while (scanf("%d", &code) == 1 && code != 0) {
        matrix* m = chn->head->mat;

        if (code == 2) {
            int* row = malloc(m->num_cols * sizeof(int));
            for (int i = 0; i < m->num_cols; i++) {
                scanf("%d", &row[i]);
            }
            add_row(m, row);
            free(row);
        }
        else if (code == 3) {
            int* col = malloc(m->num_rows * sizeof(int));
            for (int i = 0; i < m->num_rows; i++) {
                scanf("%d", &col[i]);
            }
            add_col(m, col);
            free(col);
        }
        else if (code == 4) {
            int num;
            scanf("%d", &num);
            increment(m, num);
        }
        else if (code == 5) {
            int num;
            scanf("%d", &num);
            scalar_multiply(m, num);
        }
        else if (code == 6) {
            int num;
            scanf("%d", &num);
            scalar_divide(m, num);
        }
        else {
            int num;
            scanf("%d", &num);
            scalar_power(m, num);
        }

        // Look ahead to check if the next code is 0
        int next_code;
        int peek = scanf("%d", &next_code);
        if (peek == 1) {
            if (next_code != 0) {
                // Put it back into the input stream
                ungetc('\n', stdin);  // To make sure next scanf reads properly
                ungetc('0' + (next_code % 10), stdin);
                if (next_code > 9) ungetc('0' + ((next_code / 10) % 10), stdin);
                if (next_code > 99) ungetc('0' + ((next_code / 100) % 10), stdin);
                // Print the matrix since next code is not 0
                print_matrix(m);
                printf("\n");
            }
        } else {
            // Print matrix if no more input
            print_matrix(m);
            printf("\n");
            break;
        }

        code = next_code;
    }
  

}

//Print the chain
void print_chain(chain * chn)
{
    if (!chn || !chn->head) return;
    node* current = chn->head;
    do
    {
        print_matrix(current->mat);
        printf('\n');
        current = current->next;
        
    } while (current != chn->head);
      
}

