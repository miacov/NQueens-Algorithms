@mainpage N-Queens Problem Algorithms

@author Marios Iacovou

@since 08/11/2019

This problem requires the program to find a pattern of queens
where no queens are at threat from another queen on a given chessboard size.

The program, to solve the problem, has the option to use one of the following algorithms:
1) DFS,
2) hill climbing with restarts,
3) simulated annealing.
A time limit is set to the program and optionally a seed for the rand()
function for algorithms 2 and 3.
More details on the algorithms can be found in their descriptions in the algorithms.h file.

Syntax for running the program requires pairs:
algorithm type (dfs, hill, or ann) + queen amount,
maxtime + maxtime number.
(optional) seed + seed number.
For example: ./<program_name> dfs 10 maxtime 60 

User's arguments are checked to see if:
a) algorithm type is paired with queen amount,
b) maxtime is paired with maxtime number,
c) seed (if it exists) is paired with seed number.
Pairs can be entered in any order and:
1) Seed is optional but if the algorithm is DFS then no seed must be entered,
2) Maxtime and algorithm type are not optional arguments,
3) Negative numbers are not accepted,
4) Argument count cannot be different than 5 or 7.
Any wrong argument results in termination.
