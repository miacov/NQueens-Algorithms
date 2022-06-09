/**
 *@file stack.h
 *@brief Functions for stack.
 *
 * This file includes function prototypes for a stack of
 * pointArrays.
 * It uses the structs Node and Point from def.h file.
 * A stack consists of a top node pointer and a size value.
 */

#ifndef STACK_H
#define STACK_H
#include "def.h"

typedef struct {
	Node *top;
	int size;
} Stack;

/**
 * @brief Function to push pointArray in stack.
 *
 * This function takes a pointer to an array of points,
 * its size, and the stack a new node will be pushed onto.
 * If a malloc fails the function returns EXIT_FAILURE, otherwise
 * a new node is pushed onto the stack. The new node consists of an
 * array of points the same (deep copied) as the parameter of the function,
 * and of the same size. The top pointer of the stack and its size are updated.
 * If stack is uninitialized EXIT_FAILURE is returned.
 *
 * @param  pointArray Array of points
 * @param  arraySize  Size of array of points
 * @param  s          Stack to push new node
 * @return            EXIT_FAILURE or EXIT_SUCCESS
 */
int push(Point *pointArray, int arraySize, Stack *s);

/**
 * @brief Function to pop top node of the stack.
 *
 * This function pops the top node of the stack and saves its point
 * array size and values into the parameters passed to it.
 * The top pointer of the stack and its size are updated.
 * If stack is uninitialized, or the stack is empty, or the parameters where
 * the values will be saved are null EXIT_FAILURE is returned.
 *
 * @param  s              Stack to pop
 * @param  retPointArray  Retrieved array of points
 * @param  retArrayLength Retrieved array of points length
 * @return                EXIT_FAILURE or EXIT_SUCCESS
 */
int pop(Stack *s, Point **retPointArray, int *retArrayLength);

/**
 * @brief Function to check if given stack is empty.
 *
 * This function checks if the size of the stack is 0 or not.
 * If the stack is empty 1 is returned, or 0 otherwise.
 * If the stack is null EXIT_FAILURE is returned.
 *
 * @param  s Stack to check
 * @return 1 if stack is empty, 0 if it's not, or EXIT_FAILURE if it's null
 */
int isEmpty(Stack *s);

/**
 * @brief Function to initialize a stack.
 *
 * This function takes in pointer to a stack pointer and uninitialized
 * the pointed stack. Its top node is set to null and it's size to 0.
 * If malloc fails EXIT_FAILURE is returned.
 *
 * @param  s pPointer to stack pointer
 * @return   EXIT_FAILURE or EXIT_SUCCESS
 */
int initStack(Stack **s);

#endif
