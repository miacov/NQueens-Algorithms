/**
 *@file def.h
 *@brief File has necessary includes and structs Node and Point.
 *
 * File is used as highest file in project.
 * Structs defined are Point and Node in file.
 * Point consists of coordinates x and y.
 * Node consists of an array of points, the array's length, and a pointer
 * to a another node next.
 */

#ifndef DEF_H
#define DEF_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for string functions
#include <errno.h>	// for errno
#include <limits.h>	// for INT_MAX
#include <time.h>	// for clock
#include <math.h>	// for exp

typedef struct {
	int x;
	int y;
} Point;

typedef struct node {
	Point *positionsArray;
	int positionsArrayLength;
	struct node *next;
} Node;

#endif
