#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct situtaion {
	int board[3][3];		/* the current state of board */
	int value;			/* the value evaluated */
	int level;			/* height of the node in the tree */
	int sign;			/* decide whether the node is to be kept, 1 for kept, 0 for to delete */
	struct situation *parent;	/* its parent */
	struct situation *child[4];	/* its sons */
} Situ;

Situ *create_root(int board[3][3]);

/* generate all the child nodes for the node */
void generate_child(Situ *s);

/* evaluate the situation */
int evaluate(Situ *s);

#define STACK_SIZE 1024

typedef struct space {
	Situ *stack[STACK_SIZE];
	int p;
} Space;

/* check if si is already in sp */
int exists(Space *sp, Situ *si);

Space *create_space(void);

/* pop the first Situ out of the stack */
Situ *pop(Space *sp);

/* push in a situation */
int push(Space *sp, Situ *si);

/* sort the stack according to the value */
void sort(Space *sp);

/* clean tree based on Space sp */
void clean_tree(Situ *root, Space *sp);

#endif
