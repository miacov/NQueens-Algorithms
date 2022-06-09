/**
 * @file algorithms.c
 * @brief Implements functions of algorithms.h file.
 */

#include "algorithms.h"

const double ALPHA = 0.001; // Used for simulated annealing algorithm

int countThreats(Point *queenPositions, int queenAmount) {
    if (queenAmount <= 1) {
        return 0;   // No threats for 1 queen (or less -> not used)
    }
    else {
        int i, j, threats = 0, x1, x2, y1, y2;
        for (i = 0; i < queenAmount; i++) {
            for (j = 0; j < queenAmount; j++) {
                // Same point
                if (i == j) {
                    continue;
                }

                // Point 1
                x1 = queenPositions[i].x;
                y1 = queenPositions[i].y;

                // Point 2
                x2 = queenPositions[j].x;
                y2 = queenPositions[j].y;

                // Check for threat
                if (x1 == x2 || y1 == y2 || abs(x1 - x2) == abs(y1 - y2)) {
                    threats++;
                }
            }
        }
        // Threats are double counted so we divide by 2
        return threats/2;
    }
}

Point *solveDFS(int N, int maxtime) {
    Stack *s;
    initStack(&s);

    Point *queenPositions; // Point array of placed queens' positions (x , y)

    // Push root chessboard with no queens in stack (start state)
    push(queenPositions, 0, s);

    int queenAmount, // Popped stack's queen amount
        threats,     // Amount of threats found
        i, foundSolution = 0, timeExpired = 0;
    Point queenMove; // Next move
    clock_t timeStart = clock(), timeElapsed; // Time counter

    // If not all options exhausted
    while(!isEmpty(s) && !timeExpired) {
        // Get top
        pop(s, &queenPositions, &queenAmount);

        // Check time interval
        timeElapsed = clock() - timeStart;
        if ((int) ((float) timeElapsed/CLOCKS_PER_SEC) >= maxtime) {
            free(queenPositions);
            break;
        }

        // Next move needs 1 more queen position allocated
        queenPositions = realloc(queenPositions, (queenAmount + 1) * sizeof(Point));

        // For all next row queen column positions (start from end)
        for (i = N - 1; i >= 0 ; i--) {
            // Check time interval
            timeElapsed = clock() - timeStart;
            if ((int) ((float) timeElapsed/CLOCKS_PER_SEC) >= maxtime) {
                timeExpired = 1;
                break;
            }

            queenMove.x = queenAmount;
            queenMove.y = i;
            queenPositions[queenAmount] = queenMove;

            threats = countThreats(queenPositions, queenAmount + 1);

            // Check time interval
            timeElapsed = clock() - timeStart;
            if ((int) ((float) timeElapsed/CLOCKS_PER_SEC) >= maxtime) {
                timeExpired = 1;
                break;
            }

            // If the move is valid
            if (threats == 0) {
                // If it's the solution then finish
                if (N == queenAmount + 1) {
                    foundSolution = 1;
                    break;
                }
                // Else push to stack
                else {
                    push(queenPositions, queenAmount + 1, s);
                }
            }
        }

        if (foundSolution) {
            break;
        }
        else {
            free(queenPositions);
        }
    }

    // Free memory blocks
    if (!isEmpty(s)) {
        Node *temp = s->top;
        while (temp != NULL) {
            free(temp->positionsArray); // Free point array
            temp = s->top->next;
            free(s->top); // Free node
            s->top = temp;
        }
    }
    free(s); // Free stack

    if (foundSolution) {
        return queenPositions;
    }
    else {
        return NULL;
    }
}

Point *solveHill(int N, int maxtime, int seed, int *restartsCount, int *movesMade) {
    srand(seed); // Seed rand()
    *movesMade = 0;
    *restartsCount = -1; // First pass from label doesn't count (will turn to 0)
    // Point array of placed queens' positions (x , y) at current state
    Point *curQueenPositions = malloc(N * sizeof(Point));

    Point Qi;
    int i, j;
    clock_t timeStart = clock(), timeElapsed; // Time counter

    restart_hill:
    (*restartsCount)++;

    // Place each queen in one row at random column
    for (i = 0; i < N; i++) {
        Qi.x = i;
        Qi.y = rand() % N;
        curQueenPositions[i] = Qi;
    }

    *movesMade = *movesMade + N; // Placed N queens

    // Check time interval
    timeElapsed = clock() - timeStart;
    if ((int) ((float) timeElapsed/CLOCKS_PER_SEC) >= maxtime) {
        free(curQueenPositions);
        return NULL; // Terminate
    }

    // Count of threats before a possible move
    int startThreats = countThreats(curQueenPositions, N);
    // Corrent chessboard from the start
    if (startThreats == 0) {
        return curQueenPositions;
    }

    // Count of threats when moving a queen to a different column
    // It holds the value of the lowest threat count of all possible moves in a row
    int curThreats = startThreats, newX = 0, newY = 0;

    move_search_hill:
    // Find a move that minimizes the threats
    // For every queen (row)
    for (i = 0; i < N; i++) {
        // For each of the columns available
        for (j = 0; j < N; j++) {
            // Check time interval
            timeElapsed = clock() - timeStart;
            if ((int) ((float) timeElapsed/CLOCKS_PER_SEC) >= maxtime) {
                free(curQueenPositions);
                return NULL; // Terminate
            }

            int prevY = curQueenPositions[i].y;

            // Can't move to same position as current
            if (j != prevY) {
                curQueenPositions[i].y = j; // Move queen to new position
                int threats = countThreats(curQueenPositions, N); // Count threats with new position
                if (threats < curThreats) {
                    curThreats = threats;
                    newX = i;
                    newY = j;
                }
                curQueenPositions[i].y = prevY; // Restore position for next j
            }
        }
    }

    // If a move was found that reduces the threats
    if (curThreats < startThreats) {
        (*movesMade)++;
        curQueenPositions[newX].y = newY;
        if (curThreats == 0) {
            return curQueenPositions;
        }
        else {
            startThreats = curThreats;
            goto move_search_hill; // Threats are not zero, find new move
        }
    }
    else {
        goto restart_hill; // Restart search
    }
}

Point *solveAnn(int N, int maxtime, int seed, int *movesMade) {
    srand(seed); // Seed rand()
    *movesMade = 0;

    // Point array of placed queens' positions (x , y) at current state
    Point *curQueenPositions = malloc(N * sizeof(Point));

    Point Qi;
    int i;
    clock_t timeStart = clock(), timeElapsed; // Time counter

    // Place each queen in one row at random column
    for (i = 0; i < N; i++) {
        Qi.x = i;
        Qi.y = rand() % N;
        curQueenPositions[i] = Qi;
    }

    // Check time interval
    timeElapsed = clock() - timeStart;
    if ((int) ((float) timeElapsed/CLOCKS_PER_SEC) >= maxtime) {
        free(curQueenPositions);
        return NULL; // Terminate
    }

    int startThreats;
    new_move_no_move:
    // Count of threats before a possible move
    startThreats = countThreats(curQueenPositions, N);
    // Corrent chessboard from the start
    if (startThreats == 0) {
        return curQueenPositions;
    }

    int randX, randY;

    new_move_made_move:
    // Check time interval
    timeElapsed = clock() - timeStart;
    if ((int) ((float) timeElapsed/CLOCKS_PER_SEC) >= maxtime) {
        free(curQueenPositions);
        return NULL; // Terminate
    }

    // Choose random queen and column
    randX = rand() % N,
    randY = rand() % N;

    int prevY = curQueenPositions[randX].y;

    curQueenPositions[randX].y = randY; // Move queen to new position
    int curThreats = countThreats(curQueenPositions, N); // Count threats with new position
    // Solution found if this queen is moved
    if (curThreats == 0) {
        return curQueenPositions;
    }

    // If the threats with the move weren't reduced
    if (!(curThreats <= startThreats)) {
        int threatDiff = startThreats - curThreats;
        double p = ALPHA * exp(threatDiff);

        double r = (double)rand() / RAND_MAX; // r in [0,1]

        if (!(r <= p)) {
            // Discard move
            curQueenPositions[randX].y = prevY; // Restore position
            goto new_move_no_move;
        }
    }
    // If the threats with the move were reduced
    // Or weren't but randomly chose to keep the move then
    // Keep the move and make next move
    startThreats = curThreats;
    (*movesMade)++;
    goto new_move_made_move;
}

#ifdef DEBUG_ALGORITHMS
/**
 * @brief Main used for testing.
 * @return Returns 0 for if no errors occur.
 */
int main() {
    int queenAmount = 10,
        maxtime = 60,
        seed = 10,
        isDFS = 1,
        isHill = 0,
        isAnn = 0;

    printf("Algorithm is DFS?  %d\n", isDFS);
    printf("Algorithm is Hill? %d\n", isHill);
    printf("Algorithm is Ann?  %d\n", isAnn);

    printf("\nQueens are %d\n", queenAmount);
    printf("Maxtime is %d\n", maxtime);
    if (!isDFS)
    printf("Seed is %d\n", seed);

    Point *solution;
    clock_t startTime, elapsedTime;

    if (isDFS) {
        startTime = clock();
        solution = solveDFS(queenAmount, maxtime);
        elapsedTime = clock() - startTime;
    }
    else if (isHill) {
        startTime = clock();
        solution = solveHill(queenAmount, maxtime, seed);
        elapsedTime = clock() - startTime;
    }
    else if (isAnn) {
        startTime = clock();
        solution = solveAnn(queenAmount, maxtime, seed);
        elapsedTime = clock() - startTime;
    }

    if (solution == NULL) {
        printf("\nNO SOLUTION FOUND\n");
        printf("\nTime spent: %f secs\n", (float) elapsedTime/CLOCKS_PER_SEC);
    }
    else {
        printf("\nSOLUTION FOUND\n\n");
        int row, col;
        for (row = 0; row < queenAmount; row++) {
            for (col = 0; col < queenAmount; col++) {
                if (solution[row].y == col) {
                    printf("Q ");
                }
                else {
                    printf("+ ");
                }
            }
            printf("\n");
        }
        free(solution);

        printf("\nTime spent: %f secs\n", (float) elapsedTime/CLOCKS_PER_SEC);
    }

    return 0;
}
#endif
