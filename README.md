# Quicksort pivot-picking strategies comparison

`genlist.rb` generates files with lists of numbers to sort -- one with all the
same elements, one sorted, one reverse sorted, 1000 random permutations with no
repeated elements, 1000 random permutations with repeated elements. The number
of elements in each list is given as the only argument.

`qs-pivot.c` takes a file that contains one list to sort per line (as generated
by `genlist.rb`) and runs different pivot-picking quicksorts and insertion sort
for comparison on it. It outputs the runtime for each algorithm on each list.
Each run is repeated a number of times (default 100) to get more reliable
measurements.
