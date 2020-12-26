# sim-anneal-sudoku
An (admittedly overkill) sudoku solver that uses simulated annealing

1. SimulatedAnnealing_MIS.cpp uses the same technique as when using simulated annealing to solve the maximum independent set problem; at each step it fills in an empty cell and removes all filled cells that cause a contradiction until it fills the entire board
2. SimulatedAnnealing_swaps.cpp fills in the board with the correct number of 1s, 2s, ..., 9s and then randomly exchanges the cells until there are no contradictions
3. SimulatedAnnealing_colour.cpp treats sudoku as a graph colouring problem and reassigns the numbers on each cell until the board only contains 9 distinct numbers (which we can then enumerate as 1, 2, ... 9)

## Input
The input must be in the same format as sudoku.txt, although the `-` characters can be replaced by any character that is not a digit between `1` and `9`. 

## Output
The output format will the same as sudoku_solved.txt.
