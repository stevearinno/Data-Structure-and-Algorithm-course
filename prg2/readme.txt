1. map
For the 2nd phase of the program, I use map to store all the xpoints, because in some functions
it needs to be sorted by the coordinate.

2. unordered_set
For the edges, I use unordered_set, because the searching and erasing performance is important, but not sorting. Especially to store gray/black nodes, I use this in marked_xpoints_set which I created to store these gray/black nodes.

3. vector
Most of the time, I also use vector to fit the required data structure output. Also for Kruskal's algorithm (trim_fibre_network), I use it for saving the coordinates of each set. I have no idea how to use disjoint set yet to implement Kruskal.

4. set
I use set when the requirement is to sort the coordinate, for example all_fibres().

5. priority_queue
It is for implementation of Djikstra.

6. queue
It is for implementation of BFS.

7. stack
It is for implementation of DFS.

8. unordered_map
I use unordered_map for Kruskal's algorithm to save the set number. (trim_fibre_network)

