/* 
	nodes.c: the structure of nodes, and some functions 
		to deal with it
	written by joel
*/

#include <stdio.h>
#include <stdlib.h>

#include "nodes.h"

/* evaluate the value for s */
int evaluate(Situ *s) {
	int value = 0;
	
	/* force to calculate the value of the board */
	if (s->board[0][0] != 1) 
		value ++;
	if (s->board[0][1] != 2) 
		value ++;
	if (s->board[0][2] != 3) 
		value ++;
	if (s->board[1][2] != 4) 
		value ++;
	if (s->board[2][2] != 5) 
		value ++;
	if (s->board[2][1] != 6) 
		value ++;
	if (s->board[2][0] != 7) 
		value ++;
	if (s->board[1][0] != 8) 
		value ++;
	if (s->board[1][1] != 0) 
		value ++;
	value += s->level;
	s->value = value;
	return value;
}

Situ *initialize(int seed) {
	Situ *begin = (Situ*)malloc(sizeof(Situ));
	int nums[8] = {0};
	int i, j, h;

	srand(seed);

	/* initialize the borad */
	for (i = 0; i < 3; i ++) 
		for (j = 0; j < 3; j ++) 
			begin->board[i][j] = 0;
	
	for (i = 0; i < 8; i ++) {
		while (1) {
			j = rand() % 3;
			h = rand() % 3;
			if (!begin->board[j][h]) {
				begin->board[j][h] = i + 1;
				break;
			}
		}
	}

	/* initialize pointers */
	begin->parent = NULL;
	for (i = 0; i < 4; i ++) 
		begin->son[i] = NULL;
	
	begin->level = 0;
	evaluate(begin);

	return begin;
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/* get a son with parent's borad copied */
Situ *_copy(Situ *parent) {
	Situ *son = (Situ*)malloc(sizeof(Situ));
	int i, j;

	if (!parent) {
		fprintf(stderr, "nodes.c: _copy(): parent is null\n");
		return NULL;
	}

	for (i = 0; i < 3; i ++) 
		for (j = 0; j < 3; j ++) 
			son->board[i][j] = parent->board[i][j];
	son->level = parent->level + 1;
	son->value = 256;
	son->parent = parent;
	for (i = 0; i < 4; i ++) 
		son->son[i] = NULL;
	
	return son;
}

/* generate the sons of a node */
int generate_son(Situ *parent, List *list) {
	int x, y;
	int num_of_son = 0;
	int i = 0;
	Situ *tmp = NULL;

	if (parent == NULL) {
		fprintf(stderr, "nodes.c: generate_son(): parent is null\n");
		return 0;
	}

	if (list == NULL) {
		fprintf(stderr, "node.c: generate_son(): list is null\n");
		return 0;
	}
	
	/* find the '0' in the board */
	for (x = 0; x < 3; x ++) 
		for (y = 0; y < 3; y ++) 
			if (parent->board[x][y] == 0) 
				goto find;
	find:
	/* generate sons and evaluate their values */
	switch (x) {
		case 0: 
		case 2: 
			swap(&(parent->board[x][y]), &(parent->board[1][y]));
			if (!exists(list, parent)) {
				tmp = parent->son[num_of_son] = _copy(parent);
				if (tmp) {
					evaluate(tmp);
					add_list(list, tmp);
					num_of_son ++;
				}
			}
			swap(&(parent->board[x][y]), &(parent->board[1][y]));
			break;
		case 1: 
			swap(&(parent->board[x][y]), &(parent->board[0][y]));
			if (!exists(list, parent)) {
				tmp = parent->son[num_of_son] = _copy(parent);
				if (tmp) {
					evaluate(tmp);
					add_list(list, tmp);
					num_of_son ++;
				}
			}
			swap(&(parent->board[x][y]), &(parent->board[0][y]));
			swap(&(parent->board[x][y]), &(parent->board[2][y]));
			if (!exists(list, parent)) {
				tmp = parent->son[num_of_son] = _copy(parent);
				if (tmp) {
					evaluate(tmp);
					add_list(list, tmp);
					num_of_son ++;
				}
			}
			swap(&(parent->board[x][y]), &(parent->board[2][y]));
			break;
		default: 
			fprintf(stderr, "nodes.c: generate_son(): %d: invalid value of x\n", x);
	}
	switch (y) {
		case 0:
		case 2: 
			swap(&(parent->board[x][y]), &(parent->board[x][1]));
			if (!exists(list, parent)) {
				tmp = parent->son[num_of_son] = _copy(parent);
				if (tmp) {
					evaluate(tmp);
					add_list(list, tmp);
					num_of_son ++;
				}
			}
			swap(&(parent->board[x][y]), &(parent->board[x][1]));
			break;
		case 1: 
			swap(&(parent->board[x][y]), &(parent->board[x][0]));
			if (!exists(list, parent)) {
				tmp = parent->son[num_of_son] = _copy(parent);
				if (tmp) {
					evaluate(tmp);
					add_list(list, tmp);
					num_of_son ++;
				}
			}
			swap(&(parent->board[x][y]), &(parent->board[x][0]));
			swap(&(parent->board[x][y]), &(parent->board[x][2]));
			if (!exists(list, parent)) {
				tmp = parent->son[num_of_son] = _copy(parent);
				if (tmp) {
					evaluate(tmp);
					add_list(list, tmp);
					num_of_son ++;
				}
			}
			swap(&(parent->board[x][y]), &(parent->board[x][2]));
			break;
		default: 
			fprintf(stderr, "nodes.c: generate_son(): %d: invalid value of y\n", y);
	}

	return num_of_son;
}
