/**
 * @file nQueens.c
 * @brief Uses algorithms to solve the n Queens problem.
 *
 * This program to solve the n Queens problem has the option of:
 * 1) DFS,
 * 2) hill climbing with restarts,
 * 3) simulated annealing
 * This problem requires the program to find a pattern of queens
 * where no queens are at threat from another queen on a given chessboard
 * size.
 * A time limit is set to the program and optionally a seed for the rand()
 * function for algorithms 2 and 3.
 */

#include "algorithms.h"

/**
 * @brief Main function used to run the program.
 *
 * Main checks user's arguments to see if:
 * a) algorithm type is paired with queen amount,
 * b) maxtime is paired with maxtime number,
 * c) seed (if it exists) is paired with seed number.
 * Pairs can be entered in any order and:
 * 1) Seed is optional but if the algorithm is DFS then no seed must be entered,
 * 2) Maxtime and algorithm type are not optional arguments,
 * 3) Negative numbers are not accepted,
 * 4) Argument count cannot be different than 5 or 7.
 *
 * @param  argc Argument count
 * @param  argv Arguments array in string form
 * @return      Returns EXIT_FAILURE for wrong inputs else EXIT_SUCCESS.
 */
int main(int argc, char *argv[]) {
    // Incorrect amount of arguments check
    if (argc != 5 && argc != 7) {
        printf("Wrong number of arguments! Exiting...\n");
        return EXIT_FAILURE;
    }

    int i, queenAmount = 0, maxtime = 0, seed = 0,
        isDFS = 0, isHill = 0, isAnn = 0,
        foundAlgorithm = 0, foundMaxtime = 0, foundSeed = 0;
    unsigned long conv; // To convert argv[x] to unsigned long
    char *convP;        // End value pointer for conversion

    // Checking pairs of arguments starting after program name
    for (i = 1; i < argc; i += 2) {
        // Argument is maxtime
        if (strcmp(argv[i], "maxtime") == 0) {
            if (foundMaxtime) {
                printf("Maxtime argument entered twice! Exiting...\n");
                return EXIT_FAILURE;
            }
            else {
                // Check for pair
                conv = strtoul(argv[i+1], &convP, 10);
                if (errno != 0 || *convP != '\0' || conv > INT_MAX) {
                    printf("Number given for maxtime is not unsigned integer or maxtime isn't paired! Exiting...\n");
                    return EXIT_FAILURE;
                }
                else {
                    maxtime = conv;
                    foundMaxtime = 1;
                }
            }
        }

        // Argument is seed
        else if (strcmp(argv[i], "seed") == 0) {
            if (foundSeed) {
                printf("Seed argument entered twice! Exiting...\n");
                return EXIT_FAILURE;
            }
            else {
                // Check for pair
                conv = strtoul(argv[i+1], &convP, 10);
                if (errno != 0 || *convP != '\0' || conv > INT_MAX) {
                    printf("Number given for seed is not unsigned integer or seed isn't paired! Exiting...\n");
                    return EXIT_FAILURE;
                }
                else {
                    seed = conv;
                    foundSeed = 1;
                }
            }
        }

        // Argument is algorithm DFS
        else if (strcmp(argv[i], "dfs") == 0) {
            if (foundAlgorithm) {
                printf("Algorithm argument entered twice! Exiting...\n");
                return EXIT_FAILURE;
            }
            else {
                // Check for pair
                conv = strtoul(argv[i+1], &convP, 10);
                if (errno != 0 || *convP != '\0' || conv > INT_MAX) {
                    printf("Number given for N is not positive integer or algorithm isn't paired! Exiting...\n");
                    return EXIT_FAILURE;
                }
                else {
                    queenAmount = conv;
                    foundAlgorithm = 1;
                    isDFS = 1;
                }
            }
        }

        // Argument is hill
        else if (strcmp(argv[i], "hill") == 0) {
            if (foundAlgorithm) {
                printf("Algorithm argument entered twice! Exiting...\n");
                return EXIT_FAILURE;
            }
            else {
                conv = strtoul(argv[i+1], &convP, 10);
                if (errno != 0 || *convP != '\0' || conv > INT_MAX) {
                    printf("Number given for N is not positive integer or algorithm isn't paired! Exiting...\n");
                    return EXIT_FAILURE;
                }
                else {
                    queenAmount = conv;
                    foundAlgorithm = 1;
                    isHill = 1;
                }
            }
        }

        // Argument is ann
        else if (strcmp(argv[i], "ann") == 0) {
            if (foundAlgorithm) {
                printf("Algorithm argument entered twice! Exiting...\n");
                return EXIT_FAILURE;
            }
            else {
                conv = strtoul(argv[i+1], &convP, 10);
                if (errno != 0 || *convP != '\0' || conv > INT_MAX) {
                    printf("Number given for N is not positive integer or algorithm isn't paired! Exiting...\n");
                    return EXIT_FAILURE;
                }
                else {
                    queenAmount = conv;
                    foundAlgorithm = 1;
                    isAnn = 1;
                }
            }
        }

        // Invalid argument
        else {
            printf("Wrong argument or bad pair of arguments! Exiting...\n");
            return EXIT_FAILURE;
        }
    }

    // Missing necessary arguments
    if (!foundMaxtime || !foundAlgorithm) {
        printf("Necessary arguments are maxtime and algorithm. Not all were entered! Exiting...\n");
        return EXIT_FAILURE;
    }

    // DFS with seed argument
    if (isDFS && foundSeed) {
        printf("DFS algorithm can't take seed argument! Exiting...\n");
        return EXIT_FAILURE;
    }

    // Zero queens -- invalid chessboard
    if (queenAmount == 0) {
        printf("Queens can't be zero! Exiting...\n");
        return EXIT_FAILURE;
    }

    // Non-DFS algorithm and seed not given
    // Set current time as seed instead
    if (!isDFS && !foundSeed) {
        seed = clock();
    }

    Point *solution = NULL;
    clock_t startTime = 0, elapsedTime = 0;
    int restartsCount, movesMade;
    if (isDFS) {
        startTime = clock();
        solution = solveDFS(queenAmount, maxtime);
        elapsedTime = clock() - startTime;
    }
    else if (isHill) {
        startTime = clock();
        solution = solveHill(queenAmount, maxtime, seed, &restartsCount, &movesMade);
        elapsedTime = clock() - startTime;
    }
    else if (isAnn) {
        startTime = clock();
        solution = solveAnn(queenAmount, maxtime, seed, &movesMade);
        elapsedTime = clock() - startTime;
    }

    if (solution == NULL) {
        printf("NO SOLUTION FOUND\n");
    }
    else {
        printf("SOLUTION FOUND\n\n");
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
        if (isHill) {
            printf("Restarts made to solve the problem: %d\n", restartsCount);
        }
        if (isHill || isAnn) {
            printf("Queens placed or moved to solve the problem: %d\n", movesMade);
        }
    }

    return EXIT_SUCCESS;
}
