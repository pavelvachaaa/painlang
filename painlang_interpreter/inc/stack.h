/* PRK stack library header file */
/* Created by LenkaKT, lenka.koskova.triskova@tul.cz, 28. 3. 2022 */

/* The max. stack size -- the max. element of subtrees in the main expression tree */
#ifndef PRK_STACK_H
#define PRK_STACK_H

/* header file contents go here */



#define STACK_SIZE 1000

/* If defined, debug strings are printed out. */
#define STACK_DEBUG 1

/* declarations */

int stack_top = -1;
int stack[STACK_SIZE];
const int stack_size = STACK_SIZE;

int stack_pop(int stack[], int *top, int stackSize);
int stack_push(int value, int stack[], int *top, int stackSize);

#endif /* PRK_STACK_H */
