/* 
	written by joel
*/

#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

Situ *create_root(int board[3][3]) {
	Situ *begin = (Situ*)malloc(sizeof(Situ));
	int i, j;

	/* initialize the borad */
	for (i = 0; i < 3; i ++) 
		for (j = 0; j < 3; j ++) 
			begin->board[i][j] = board[i][j];
	
	/* initialize pointers */
	begin->parent = NULL;
	begin->level = 0;
	begin->sign = 0;
	evaluate(begin);
	for (i = 0; i < 4; i ++) 
		begin->child[i] = NULL;

	return begin;
}

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

void _swap_int(int *a , int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/* check if two situations have the same board */
int _board_equals(Situ *a, Situ *b) {
	int i, j;

	if (a != NULL && b != NULL) {
		for (i = 0; i < 3; i ++) 
			for (j = 0; j < 3; j ++) 
				if (a->board[i][j] != b->board[i][j]) 
					return 0;
		return 1;
	}

	/* we return 0 if any of the situs is null */
	return 0;
}

int _appears(Situ *node) {
	Situ *tmp;

	if (node != NULL) {
		tmp = node->parent;

		while (tmp) {
			if (_board_equals(tmp, node)) 
				return 1;
			tmp = tmp->parent;
		}
	}

	return 0;
}

Situ *_copy_Situ(Situ *parent) {
	Situ *tmp = NULL;
	int i, j;

	if (parent != NULL) {
		tmp = (Situ*)malloc(sizeof(Situ));
		if (!tmp) 
			return NULL;
		for (i = 0; i < 3; i ++)	/* copy the board */ 
			for (j = 0; j < 3; j ++) 
				tmp->board[i][j] = parent->board[i][j];
		tmp->level = parent->level + 1;
		evaluate(tmp);
		tmp->parent = parent;
		tmp->sign = 0;
		for (i = 0; i < 4; i ++) 
			tmp->child[i] = NULL;
	}

	return tmp;
}

void generate_child(Situ *s) {
	int i, j;
	int num_of_child = 0;
	Situ *tmp;

	if (s == NULL) 
		return ;
	/* find the location of '0' */
	for (i = 0; i < 3; i ++) 
		for (j = 0; j < 3; j ++) 
			if (s->board[i][j] == 0) 
				goto find;
	find:
	switch (i) {
		case 0: 
		case 2: 
			_swap_int(&(s->board[i][j]), &(s->board[1][j]));
			/* make sure the board is not as the same as its parent */
			if (!_appears(s)) {
				tmp = _copy_Situ(s);
				if (tmp) 
					s->child[num_of_child ++] = tmp;
				else 
					fprintf(stderr, "failed to generate a child situation\n");
			}
			_swap_int(&(s->board[i][j]), &(s->board[1][j]));
			break;
		case 1: 
			_swap_int(&(s->board[i][j]), &(s->board[0][j]));
			if (!_appears(s)) {
				tmp = _copy_Situ(s);
				if (tmp) 
					s->child[num_of_child ++] = tmp;
				else 
					fprintf(stderr, "failed to generate a child situation\n");
			}
			_swap_int(&(s->board[i][j]), &(s->board[0][j]));

			_swap_int(&(s->board[i][j]), &(s->board[2][j]));
			if (!_appears(s)) {
				tmp = _copy_Situ(s);
				if (tmp) 
					s->child[num_of_child ++] = tmp;
				else 
					fprintf(stderr, "struct.c: generate_child(): failed to generate a child\n");
			}
			_swap_int(&(s->board[i][j]), &(s->board[2][j]));
			break;
		default: 
			fprintf(stderr, "struct.c: generate_child(): invalid value of i: %d\n", i);
			break;
	}

	switch (j) {
		case 0: 
		case 2: 
			_swap_int(&(s->board[i][j]), &(s->board[i][1]));
			/* make sure the board is not as the same as its parent */
			if (!_appears(s)) {
				tmp = _copy_Situ(s);
				if (tmp) 
					s->child[num_of_child ++] = tmp;
				else 
					fprintf(stderr, "failed to generate a child\n");
			}
			_swap_int(&(s->board[i][j]), &(s->board[i][1]));
			break;
		case 1: 
			_swap_int(&(s->board[i][j]), &(s->board[i][0]));
			if (!_appears(s)) {
				tmp = _copy_Situ(s);
				if (tmp) 
					s->child[num_of_child ++] = tmp;
				else 
					fprintf(stderr, "failed to generate a child\n");
			}
			_swap_int(&(s->board[i][j]), &(s->board[i][0]));

			_swap_int(&(s->board[i][j]), &(s->board[i][2]));
			if (!_appears(s)) {
				tmp = _copy_Situ(s);
				if (tmp) 
					s->child[num_of_child ++] = tmp;
				else 
					fprintf(stderr, "failed to generate a child\n");
			}
			_swap_int(&(s->board[i][j]), &(s->board[i][2]));
			break;
		default: 
			fprintf(stderr, "struct.c: generate_child(): invalid value of j: %d\n", j);
			break;
	}
}

void _mark_nodes(Space *sp, int mark) {
	int i;
	Situ *tmp;

	if (sp) {
		for (i = 0; i < sp->p; i ++) {
			tmp = sp->stack[i];
			/* mark the node and its ancestors as sign = mark */
			while (tmp) {
				tmp->sign = mark;
				tmp = tmp->parent;
			}
		}
	}
}

/* delete all the nodes on the tree with sign = 0 */
void _delete_nodes(Situ *root) {
	int i = 0;

	if (root) {
		while (root->child[i]) 
			_delete_nodes(root->child[i ++]);
		if (root->sign == 0) 
			free(root);
	}
}

void clean_tree(Situ *root, Space *sp) {
	if (root) {
		_mark_nodes(sp, 1);
		_delete_nodes(root);
		_mark_nodes(sp, 0);
	}
	printf("clean\n");
}

int exists(Space *sp, Situ *si) {
	int i;

	if (sp != NULL) {
		for (i = 0; i < sp->p; i ++) 
			if (si == sp->stack[i]) 
				return i;	/* element found */
	}

	/* here we define the default value to be -1, no matter if sp 
		or si is null. no error information will be given */
	return -1;
}

Space *create_space(void) {
	Space *tmp = (Space*)malloc(sizeof(Space));
	
	if (tmp != NULL) {
		tmp->p = 0;
		for (int i = 0; i < STACK_SIZE; i ++) 
			tmp->stack[i] = NULL;
	}
	else 
		fprintf(stderr, "struct.c: create_space(): failed to create space\n");
	
	return tmp;
}

Situ *pop(Space *sp) {
	if (sp != NULL) {
		printf("pop(): p = %d\n", sp->p);
		if (sp->p <= 0) 
			fprintf(stderr, "struct.c: pop(): stack is empty\n");
		else 
			return sp->stack[-- (sp->p)];
	}

	return NULL;
}

#define REDUCE_SIZE 100

/* reduce the nodes in the space, keep only the top REDUCE_SIZE nodes 
	with a lower value */
void _reduce(Space *sp) {
	int i;
	
	if (sp) {
		if (sp->p <= REDUCE_SIZE * 2) 
			return ;	/* the capacity of the stack is less than REDUCE_SIZE */
		i = sp->p - REDUCE_SIZE;
		for (sp->p = 0; sp->p < REDUCE_SIZE; sp->p ++) 
			sp->stack[sp->p] = sp->stack[i ++];
	}
}

int push(Space *sp, Situ *si) {
	if (sp != NULL && si != NULL) {
		printf("push(): p = %d\n", sp->p);
		if (sp->p >= STACK_SIZE) {
			_reduce(sp);	/* if the stack is full, remove the bottom nodes to make space */
			sp->stack[sp->p ++] = si;
			return 1;	/* return 1 to show that the stack is recently reduced */
		}
		else 
			sp->stack[sp->p ++] = si;
	}

	return 0;
}

void _swap_situ_p(Situ **a, Situ **b) {
	Situ *tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort(Space *sp) {
	int i, j;

	if (sp == NULL) 
		return ;
	
	for (i = sp->p - 1; i > 0; i --) {
		for (j = 0; j < i; j ++) {
			if (sp->stack[j]->value < sp->stack[j + 1]->value) 
				_swap_situ_p(&(sp->stack[j]), &(sp->stack[j + 1]));
		}
	}
}
