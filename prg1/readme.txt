Name: Stefanus Wirdatmadja
Student no: 232722

For this programming assignment, I am using the unordered map to save all the beacon data.
I use beaconID as the key and the value is the Beacon struct. I use the beaconID as the key
because it is unique for each beam.
Performance-wise, the unordered map has the average performance of theta(1) and O(n) to add,
remove, and search. These activities are used in all the other functions, for example we need
to find the beacon ID (search) before doiang any other activity.

I burden some activities on the "add_beacon" such as total_color, min_brightness,
max_brightness because the total_color is called more often than others, min and max because
it is easier to keep it updated everytime the new beacon is added and it takes only constant
time.

For sorting, many of them I use the data structure instead of built-in sort vector from C++,
because based on my analysis, the performance is better to move from one data structure to
another.

For each functions, I put on the comments in header file, so for more details, please refer
to the header file.
