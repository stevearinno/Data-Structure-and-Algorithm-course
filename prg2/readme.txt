1. map
For the 2nd phase of the program, I use map to store all the xpoints, because in some functions
it needs to be sorted by the coordinate.

2. unordered_set
For the edges, I use unordered_set, because the searching and erasing performance is important, but not sorting. Especially to store gray/black nodes, I use this in marked_xpoints_set which I created to store these gray/black nodes.

3. vector
Most of the time, I also use vector to fit the required data structure output.

4. set
I use set when the requirement is to sort the coordinate, for example all_fibres().

5. priority_queue
It is for implementation of Djikstra.

6. queue
It is for implementation of BFS.

7. stack
It is for implementation of DFS.

Note:
I realize that my trim_fibre_network performance is so bad, sometimes it crashes due to memory
allocation problem. However, many times it works, please run it using individual perftest_trim
