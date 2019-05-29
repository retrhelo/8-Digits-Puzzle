/*
	display.c: some functions for displaying the result onto the screen
	written by joel
*/

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdio.h>

#include "struct.h"

/* display the borad of s */
void show_Situ(Situ *s);

/* display the record of path */
void show_record(Space *record);

void check_stack(Space *sp);

#endif
