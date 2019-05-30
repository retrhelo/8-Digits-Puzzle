#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct situtaion {
	int board[3][3];		/* the current state of board */
	int match;			/* how well the nodes matches the final situation */
	int value;			/* the value evaluated */
	int level;			/* height of the node in the tree */
	struct situation *parent;	/* its parent */
} Situ;

Situ *create_root(int board[3][3]);

/* generate all the child nodes for the node */
void generate_child(Situ *s);

/* evaluate the situation */
int evaluate(Situ *s);

#define STACK_SIZE 102400

typedef struct space {
	Situ *stack[STACK_SIZE];
	int p;
} Space;

/* below are two spaces to be used in the program, 
	make sure they are initialized at the beginning 
	of the program */
extern Space *open;	/* store the nodes that are not spawned */
extern Space *close;	/* store the nodes that are spawned */

/* check if si is already in sp */
int exists(Space *sp, Situ *si);

Space *create_space(void);

/* pop the first Situ out of the stack */
Situ *pop(Space *sp);

/* push in a situation */
void push(Space *sp, Situ *si);

/* sort the stack according to the value */
void sort(Space *sp);

#endif
