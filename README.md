# sim-anneal-sudoku
A (admittedly overkill) sudoku solver that uses simulated annealing

1. SimulatedAnnealing_MIS.cpp uses the same technique as when using simulated annealing to solve the maximum independent set problem; at each step it fills in an empty cell and removes all filled cells that cause a contradiction until it fills the entire board
2. SimulatedAnnealing_swaps.cpp fills in the board with the correct number of 1s, 2s, ..., 9s and then randomly exchanges the cells until there are no contradictions
3. SimulatedAnnealing_colour.cpp treats sudoku as a graph colouring problem and reassigns the numbers on each cell until the board only contains 9 distinct numbers (which we can then enumerate as 1, 2, ... 9)
