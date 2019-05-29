/* 
	written by joel
*/

#include "display.h"

void show_Situ(Situ *s) {
	int i, j;

	if (s != NULL) {
		printf("level: %d\n", s->level);
		printf("value: %d\n", s->value);
		for (i = 0; i < 3; i ++) {
			for (j = 0; j < 3; j ++) 
				printf("%3d", s->board[i][j]);
			putchar('\n');
		}
	}
}

void show_record(Space *record) {
	Situ *tmp;

	if (record != NULL) {
		while (tmp = pop(record)) {
			show_Situ(tmp);
			printf("===================\n");
		}
	}
}

void check_stack(Space *sp) {
	int i;

	if (sp != NULL) {
		printf("stack size: %d\n", sp->p);
		for (i = sp->p; i >= 0; i --) {
			printf("stack: %d\n", i);
			show_Situ(sp->stack[i]);
		}
	}
}
