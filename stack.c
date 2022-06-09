/**
 * @file stack.c
 * @brief Implements functions of stack.h file.
 */

#include "stack.h"

int push(Point *pointArray, int arraySize, Stack *s) {
	// Bad entries check
	if (s == NULL)
		return EXIT_FAILURE;

	// Initialize new node
	Node *temp = (Node *) malloc(sizeof(Node));
	if (temp == NULL)
		return EXIT_FAILURE;

	// Initialize new node fields
	temp->positionsArray = (Point *) malloc(arraySize*sizeof(Point));
	if (temp->positionsArray == NULL)
		return EXIT_FAILURE;

	temp->positionsArrayLength = arraySize;

	// Deep copy pointArray
	for (--arraySize; arraySize >= 0; --arraySize) {
		temp->positionsArray[arraySize] = pointArray[arraySize];
	}

	// New pushed node is now top
	temp->next = s->top;
	s->top = temp;

	// Increase stack size
	(s->size)++;

	return EXIT_SUCCESS;
}

int pop(Stack *s, Point **retPointArray, int *retArrayLength) {
	// Bad entries check
	if (s->size == 0 || s == NULL || retPointArray == NULL || retArrayLength == NULL)
		return EXIT_FAILURE;

	// Save top node's array of pointers and its size in parameters given
	*retPointArray = (s->top)->positionsArray;
	*retArrayLength = (s->top)->positionsArrayLength;

	// Pop the node and deallocate it
	Node *temp = s->top->next;
	free(s->top);
	s->top = temp;

	// Decrease stack size
	(s->size)--;

	return EXIT_SUCCESS;
}

int isEmpty(Stack *s) {
	if (s == NULL)
		return EXIT_FAILURE;

	return (s->size == 0) ? 1 : 0;
}

int initStack(Stack **s) {
	if (s == NULL)
		return EXIT_FAILURE;

	*s = (Stack *) malloc(sizeof(Stack));
	if (*s == NULL)
		return EXIT_FAILURE;

	(*s)->top = NULL;
	(*s)->size = 0;

	return EXIT_SUCCESS;
}

#ifdef DEBUG_STACK
/**
 * @brief Main used for testing.
 * @return Returns 0 for if no errors occur.
 */
int main() {
    Stack *s;
    initStack(&s);

    Point *pointArray = malloc(5*sizeof(Point));

    Point p1,p2,p3,p4,p5;
    p1.x = 5;
    p1.y = 5;

    p2.x = 7;
    p2.y = 6;

    p3.x = 2;
    p3.y = 1;

    p4.x = 6;
    p4.y = 4;

    p5.x = 0;
    p5.y = 0;

    pointArray[0] = p1;
    pointArray[1] = p2;
    pointArray[2] = p3;
    pointArray[3] = p4;
    pointArray[4] = p5;

    printf("Push completed successfully (expected 0): %d\n", push(pointArray, 5, s));

    pointArray[0] = p5;
    pointArray[1] = p4;
    pointArray[2] = p3;
    pointArray[3] = p2;
    pointArray[4] = p1;

    printf("Push completed successfully (expected 0): %d\n", push(pointArray, 5, s));

    Point *pop1, *pop2;
    int size1, size2;

	printf("\nStack is empty (expected 0): %d\n", isEmpty(s));
    printf("Pop completed successfully (expected 0): %d\n", pop(s, &pop1, &size1));
    printf("Pop completed successfully (expected 0): %d\n", pop(s, &pop2, &size2));
    printf("Stack is empty (expected 1): %d\n", isEmpty(s));

    int i;
    printf("\nFirst popped array has size of %d\n", size1);
    for (i = 0; i < 5; i++) {
        printf("First pop x and y are: %d , %d \n", pop1[i].x , pop1[i].y);
    }

    printf("\nSecond popped array has size of %d\n", size2);
    for (i = 0; i < 5; i++) {
        printf("Second pop x and y are: %d , %d \n", pop2[i].x , pop2[i].y);
    }

	printf("\nPop completed unsuccessfully (expected 1): %d\n", pop(s, &pop2, &size2));

    return 0;
}
#endif
