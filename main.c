/* 
	written by joel
*/

#include <stdio.h>
#include <stdlib.h>		/* for random number */
#include <time.h>		/* for time() */

#include "struct.h"
#include "display.h"

Situ *root = NULL;
Space *record = NULL;	/* for recording the final path */
Space *open = NULL;	/* the space storing the unspawned nodes */

/* 
void _initialize_seed(long seed) {
	int i, j, h;
	int board[3][3];

	printf("initializing: seed: %ld\n", seed);
	srand(seed);
	for (i = 0; i < 3; i ++) 
		for (j = 0; j < 3; j ++) 
			board[i][j] = 0;
	for (i = 0; i < 8; i ++) {
		while (1) {
			j = rand() % 3;
			h = rand() % 3;
			if (!board[j][h]) {
				board[j][h] = i + 1;
				break;
			}
		}
	}
	root = create_root(board);
	open = create_space();
	close = create_space();
	record = create_space();
}
*/

void _initialize_assign(void) {
	int i, j;
	int board[3][3];

	printf("assign mode:\n");
	for (i = 0; i < 3; i ++) 
		for (j = 0; j < 3; j ++) 
			scanf("%d", &board[i][j]);
	printf("input done\n");
	root = create_root(board);
	open = create_space();
	record = create_space();
}

int main(void) {
	Situ *tmp = NULL;
	int counter = 0;

	_initialize_assign();

	tmp = root;
	
	while (tmp != NULL && tmp->level != tmp->value) {
		//printf("\e[31mcurrent node\e[0m:\n");
		//show_Situ(tmp);
		generate_child(tmp);
		counter ++;
		//printf("after generation\n");
		//printf("\e[31mopen space\e[0m:\n");
		//check_stack(open);
		tmp = pop(open);
	}
	if (tmp == NULL) {
		fprintf(stderr, "main.c: main(): break the loop because tmp is null\n");
		return -1;
	}
	while (tmp) {
		push(record, tmp);
		tmp = tmp->parent;
	}
	printf("totally nodes spawned: %d\n", counter);
	show_record(record);

	return 0;
}
