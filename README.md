# Quicksort Pivot-Picking Strategies Comparison

This repository contains the code, data, and results for parts of the
experiments in the following paper:
Kotthoff, Lars, Alexandre Fréchette, Tomasz P. Michalak, Talal Rahwan, Holger H. Hoos, and Kevin Leyton-Brown. “Quantifying Algorithmic Improvements over Time.” In 27th International Joint Conference on Artificial Intelligence (IJCAI) Special Track on the Evolution of the Contours of AI, 2018.

In particular, it corrects a bug in the code and presents updated results.

`genlist.rb` generates files with lists of numbers to sort -- one with all the
same elements, one sorted, one reverse sorted, 1000 random permutations with no
repeated elements, 1000 random permutations with repeated elements. The number
of elements in each list is given as the only argument.

`qs-pivot.c` takes a file that contains one list to sort per line (as generated
by `genlist.rb`) and runs different pivot-picking quicksorts and insertion sort
for comparison on it. It outputs the runtime for each algorithm on each list.
Each run is repeated a number of times (default 100) to get more reliable
measurements.
