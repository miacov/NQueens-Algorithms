# Algorithms for the N-Queens Problem
Using different algorithms written in C to solve the N-queens problem.

Algorithms implemented: Depth-First Search, Random-Restart Hill Climbing, Simulated Annealing

## N-Queens Problem
* It's the problem of placing N queens on an NxN chessboard so that no queens attack each other. A solution to this problem exists for all natural numbers besides N=2 and N=3. 

* A queen Qi at a position (Xi, Yi) threatens a queen Qj at a position (Xj, Yj) if any of the following conditions are true:
  * They are on the same row: Xi = Xj
  * They are on the same column: Yi = Yj
  * They are on the same diagonal: |Xi - Xj| = |Yi - Yj|

## Depth-First Search

This algorithm performs an exhaustive search of states of the problem.

> 1. Start with an empty stack
> 1. Push the initial state (no queens on board) on the stack
> 1. While the stack is not empty:
>     1. Pop the stack to get state V
>     1. For each valid next state Vi of state V (one more queen placed):
>         1. If state Vi is a solution then return it and finish
>         1. Else push state Vi at the top of the stack
> 1. Return no solution exists (empty stack)

## Random-Restart Hill Climbing
This algorithm performs a series of hill-climbing searches from randomly-generated initial states. It incrementally changes a single element in a state in an attempt to find a state closer to the solution. Restarts are used as the algorithm can get stuck at a local optimum that doesn't solve the problem. As this algorithm may run indefinitely without finding a solution, a time limit is imposed.

> 1. Place each queen Qi, i=1..N, at position (i, Yi), where Yi is randomly selected in range 1..N (one queen in each row)
> 1. T0 is the number of pairs of queens that attack each other
> 1. Set T=T0, x=0, y=0
> 1. For i=1..N
>     1. For j=1..N, j≠Yi
>         1. K is the number of pairs of queens that attack each other if queen Qi moved to position (i, j)
>         1. If K<T then T=K, x=i, y=j (mark position)
> 1. If T<T0 (found move that reduces attacks) then move queen Qx to position (x, y)
>     1. If T=0 (no attacks) then return the current state and finish
>     1. Else go to step 4
> 1. Else go to step 1 (restart as no move that reduces attacks was found)

## Simulated Annealing
This algorithm attempts to solve the local optima problem of the hill-climbing algorithm by permitting some "bad" moves that increase the number of queens that attack each other. This helps to escape states that lead to a local optimum. The probability of permitting these moves is determined by the size of the increase of the number of queen threats. Permitting these moves means no restarts are used. As this algorithm may run indefinitely without finding a solution, a time limit is imposed.

> 1. Place each queen Qi, i=1..N, at position (i, Yi), where Yi is randomly selected in range 1..N (one queen in each row)
> 1. T0 is the number of pairs of queens that attack each other
> 1. Choose a queen Qx, x=1..N, and a column y in range 1..N randomly
> 1. T is the number of pairs of queens that attack each other if queen Qx moved to position (x, y)
> 1. If T<=T0 (found move that reduces attacks or keeps them the same) then move queen Qx to position (x, y)
>     1. If T=0 (no attacks) then return the current state and finish
> 1. Else ΔT=T0-T, ΔT<0. Probability p=α⋅e^ΔT, where 0<α<=1 is a constant (set to α=0.001). Choose a random real number r in range 0..1. If r<=p then move queen Qx to position (x, y).
> 1. Go to step 2

## Usage
### Makefile
* **make** builds the project
* **make doxy** generates doxygen documentation
* **make all** builds the project and generates doxygen documentation
* **make clean** removes all object files, executables, and doxygen files

### Running Algorithms
* Running the DFS algorithm requires the number of queens N and the max permitted time to run the program
~~~
./nQueens dfs N maxtime T
~~~

* Running the hill-climbing algorithm requires the number of queens N, the max permitted time to run the program, and a seed number for the rand() function
~~~
./nQueens hill N maxtime T seed S
~~~

* Running the simulated-annealing algorithm requires the number of queens N, the max permitted time to run the program, and a seed number for the rand() function
~~~
./nQueens ann N maxtime T seed S
~~~

### Example
~~~
./nQueens hill 10 maxtime 20 seed 5
SOLUTION FOUND

+ + + + Q + + + + + 
+ + + + + + Q + + + 
+ + + + + + + + Q + 
+ + + Q + + + + + + 
+ Q + + + + + + + + 
+ + + + + + + Q + + 
+ + + + + + + + + Q 
+ + Q + + + + + + + 
Q + + + + + + + + + 
+ + + + + Q + + + + 

Time spent: 0.005305 secs
Restarts made to solve the problem: 14
Queens placed or moved to solve the problem: 217
~~~
