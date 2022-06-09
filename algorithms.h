/**
 *@file algorithms.h
 *@brief Algorithms and helper functions to solve the nQueens problem.
 *
 * This file includes function prototypes for the algorithms to solve
 * the nQueens problem, a helper method to count pairs of queens at threat.
 * It uses the struct stack from the stack.h file.
 */

#include "stack.h"
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

/**
 * @brief Helper function to count queens at threat on chessboard.
 *
 * Function goes through the points in the array given as parameter to
 * check which queens are at threat.
 * Queens at threat include queens that are on the same row, same column,
 * or on the same diagonal line.
 *
 * @param  queenPositions Array of points with queen positions
 * @param  queenAmount    Length of queenPositions
 * @return                Returns pairs of queens at threat.
 */
int countThreats(Point *queenPositions, int queenAmount);

/**
 * @brief Function that uses a DFS algorithm to solve the nQueens problem.
 *
 * This function does an exhaustive search of solutions to the nQueens problem,
 * using a DFS algorithm. Arrays of points are pushed onto a stack to represent
 * positions of queens on a board (when placed).
 *
 * The algorithm is the following:
 * 1. Push empty array of points to stack.
 * 2. While the stack is not empty:
 * a. pop stack and get array of points (with length)
 * b. for each valid next placement (0 threats) of queen (1 more queen than popped)
 * i) if it's the solution return the new array
 * ii) else push new array with new placed queen to stack
 * 3. If no solution was found (empty stack) or time has expired return null.
 *
 * @param  N       Amount of queens.
 * @param  maxtime Max time to spend running the algorithm.
 * @return         Returns solution array of points if found or null if not.
 */
Point *solveDFS(int N, int maxtime);

/**
 * @brief Function that uses a hill climbing algorithm with restarts to solve the nQueens problem.
 *
 * This function uses hill climbing to search for the solution to the nQueens problem.
 * It takes in a parameter seed which is the seed to the rand() function used to
 * place the queens in random columns at the start. Only way for this algorithm
 * to stop is if it runs out of time (maxtime parameter), or finds the solution.
 *
 * The algorithm is the following:
 * 1. Each queen is placed in a row, at a random column.
 * 2. Count the starting threats between queens.
 * a. If it's zero return current positions.
 * 3. Set as currentThreats the startThreats.
 * 4. Change each queen's column to all the possible columns (not the current one)
 * a. Recount the threats for the position tested.
 * b. If the threats are lower than the currentThreats then
 * set the threats as currentThreats and mark the x and y of the new position.
 * 5. After the loop, if currentThreats < startThreats then
 * a. change the position of a queen to the marked one.
 * b. If currentThreats are 0 then return the positions.
 * c. If currentThreats aren't 0 (not finished) then set startThreats as currentThreats
 * and repeat the loop of step 4.
 * 6. If currentThreats aren't less than startThreats then restart the process
 * from step 1.
 *
 * @param  N             Amount of queens.
 * @param  maxtime       Max time to spend running the algorithm.
 * @param  seed          Seed for rand() function.
 * @param  restartsCount Counter of restarts to be modified and returned.
 * @param  movesMade     Counter of moves to be modified and returned.
 * @return  Returns solution array of points if found or null if out of time
 */
Point *solveHill(int N, int maxtime, int seed, int *restartsCount, int *movesMade);

/**
 * @brief Function that uses a simulated annealing algorithm to solve the nQueens problem.
 *
 * This function uses simulated annealing to search for the solution to the nQueens problem.
 * It takes in a parameter seed which is the seed to the rand() function used to
 * place the queens in random columns at the start. Only way for this algorithm
 * to stop is if it runs out of time (maxtime parameter), or finds the solution.
 * This algorithm compared to hill climbing doesn't allow restarts, and allows
 * moves that keep the threat count the same as before.
 *
 * The algorithm is the following:
 * 1. Each queen is placed in a row, at a random column.
 * 2. Count the starting threats between queens.
 * a. If it's zero return current positions.
 * 3. Choose a random queen and a random column
 * 4. Check the currentThreats count if the queen would move to that position
 * 5. If currentThreats are less or equal to startThreats
 * a. Change the position of a queen to the marked one.
 * b. If the threats are 0 then return the positions.
 * 6. If not then set as Dt = currentThreats - startThreats.
 * Set p = a * e^Dt. A is declared as a constant in the program.
 * Choose a random double r from [0,1] pool.
 * If r <= p then change the position of a queen to the marked one.
 * 7. Goto step 2.
 *
 * @param  N       Amount of queens.
 * @param  maxtime Max time to spend running the algorithm.
 * @param  seed    Seed for rand() function.
 * @param  movesMade     Counter of moves to be modified and returned.
 * @return         Returns solution array of points if found or null if out of time
 */
Point *solveAnn(int N, int maxtime, int seed, int *movesMade);

#endif
