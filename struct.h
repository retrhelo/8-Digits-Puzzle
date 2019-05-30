#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct situtaion {
	int board[3][3];		/* the current state of board */
<<<<<<< HEAD
	int value;			/* the value evaluated */
	int level;			/* height of the node in the tree */
	int sign;			/* decide whether the node is to be kept, 1 for kept, 0 for to delete */
	struct situation *parent;	/* its parent */
	struct situation *child[4];	/* its sons */
=======
	int match;			/* how well the nodes matches the final situation */
	int value;			/* the value evaluated */
	int level;			/* height of the node in the tree */
	struct situation *parent;	/* its parent */
>>>>>>> better-eval
} Situ;

Situ *create_root(int board[3][3]);

/* generate all the child nodes for the node */
void generate_child(Situ *s);

/* evaluate the situation */
int evaluate(Situ *s);

<<<<<<< HEAD
#define STACK_SIZE 1024
=======
#define STACK_SIZE 102400
>>>>>>> better-eval

typedef struct space {
	Situ *stack[STACK_SIZE];
	int p;
} Space;

<<<<<<< HEAD
=======
/* below are two spaces to be used in the program, 
	make sure they are initialized at the beginning 
	of the program */
extern Space *open;	/* store the nodes that are not spawned */
extern Space *close;	/* store the nodes that are spawned */

>>>>>>> better-eval
/* check if si is already in sp */
int exists(Space *sp, Situ *si);

Space *create_space(void);

/* pop the first Situ out of the stack */
Situ *pop(Space *sp);

/* push in a situation */
<<<<<<< HEAD
int push(Space *sp, Situ *si);
=======
void push(Space *sp, Situ *si);
>>>>>>> better-eval

/* sort the stack according to the value */
void sort(Space *sp);

<<<<<<< HEAD
/* clean tree based on Space sp */
void clean_tree(Situ *root, Space *sp);

=======
>>>>>>> better-eval
#endif
