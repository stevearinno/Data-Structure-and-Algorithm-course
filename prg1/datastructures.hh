// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <unordered_set>
#include <unordered_map>
#include <memory>

// Type for beacon IDs
using BeaconID = std::string;

// Return value for cases where required beacon was not found
BeaconID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for color (RGB)
struct Color
{
    int r = NO_VALUE;
    int g = NO_VALUE;
    int b = NO_VALUE;
};

// Equality and non-equality comparisons for Colors
inline bool operator==(Color c1, Color c2) { return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b; }
inline bool operator!=(Color c1, Color c2) { return !(c1==c2); }

// Return value for cases where color was not found
Color const NO_COLOR = {NO_VALUE, NO_VALUE, NO_VALUE};

// Type for light transmission cost (used only in the second assignment)
using Cost = int;

// Return value for cases where cost is unknown
Cost const NO_COST = NO_VALUE;

struct Beacon
{
    BeaconID id = NO_ID;
    std::string name = NO_NAME;
    Coord coord = NO_COORD;
    Color color = NO_COLOR;
    Color sum_color = NO_COLOR;
    std::unordered_set<BeaconID> parents;
    BeaconID child = NO_ID;
    int no_of_parents = 0;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: O(1) because I have already dedicate one parameter for this.
    // But if you take into account the process of counting the beacon which I do every time
    // the beacon is added, so it is O(n).
    int beacon_count();

    // Estimate of performance: O(1)
    // Short rationale for estimate: I just use one command to clear
    void clear_beacons();

    // Estimate of performance: O(n)
    // Short rationale for estimate: It is the combination of iteration O(n) and element
    // addition to a vector O(1)
    std::vector<BeaconID> all_beacons();

    // Estimate of performance: O(n)
    // Short rationale for estimate: I add the data to the unordered map, others are only O(1)
    // commands.
    bool add_beacon(BeaconID id, std::string const& name, Coord xy, Color color);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Searching through unordered map.
    std::string get_name(BeaconID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Searching through unordered map.
    Coord get_coordinates(BeaconID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Searching through unordered map.
    Color get_color(BeaconID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: The process contains iterating and moving unordered set
    // to multimap and then iterating and moving multipmap to vector. So the maximum complexity
    // is for iterating which is O(n)
    std::vector<BeaconID> beacons_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The process contains iterating and moving unordered set
    // to multimap and then iterating and moving multipmap to vector. So the maximum complexity
    // is for iterating which is O(n)
    std::vector<BeaconID> beacons_brightness_increasing();

    // Estimate of performance: O(1)
    // Short rationale for estimate: O(1) because I have already dedicate one parameter for this.
    BeaconID min_brightness();

    // Estimate of performance: O(1)
    // Short rationale for estimate: O(1) because I have already dedicate one parameter for this.
    BeaconID max_brightness();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: The process includes iterating through unordered map and
    // moving the data to a vector. Then, sorting the vector. The maximum complexity is O(n log n)
    std::vector<BeaconID> find_beacons(std::string const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Searching element in unordered map
    bool change_beacon_name(BeaconID id, std::string const& newname);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Searching element in unordered map and I also update the colors
    // of the children
    bool change_beacon_color(BeaconID id, Color newcolor);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: It has several time iteration process, but never nested iteration.
    // Other commands have only constant complexity. So the maximum complexity belongs to iteration
    // through unordered map.
    bool add_lightbeam(BeaconID sourceid, BeaconID targetid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This process includes searching element through unordered map
    // and put it into set and then move the data in the set to vector. The maximum complexity is to
    // searching the data through unordered map, which is O(n)
    std::vector<BeaconID> get_lightsources(BeaconID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This process contains searching element through unordered map
    // and pushing to a vector. The maximum complexity comes from the searching process which is O(n)
    std::vector<BeaconID> path_outbeam(BeaconID id);

    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: It contains searching element through unordered map and lots of
    // recursion due to updating the colors. Updating the colors complexity is also O(n), the same as
    // searching element through unordered map. But the complexity is added, not multiplied.
    bool remove_beacon(BeaconID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: My method is to find the root first which includes recursion, the
    // complexity of the recursion is O(n) because it narrows down the data as the recursion runs. Then
    // it iterates all the children and push it into the vector, the complexity is also O(n)
    std::vector<BeaconID> path_inbeam_longest(BeaconID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: To get the total color, it process the parameter of "total_sum" that
    // is always updated in all the activities that have effects to the color of the lightbeams. The
    // function itself has the complexity of O(n) because it searches through the unordered map and then
    // all the activities to update the color (when the beam added, removed, changed, etc) is also O(n).
    // So the maximum complexity is O(n)
    Color total_color(BeaconID id);

    std::unordered_map<BeaconID, std::shared_ptr<Beacon>> BeaconDB;



private:
    // Add stuff needed for your class implementation here
    int no_of_beacon = 0;
    BeaconID min_bright_beacon = NO_ID;
    BeaconID max_bright_beacon = NO_ID;
    int min_bright_level = 0;
    int max_bright_level = 0;

    bool find_id(BeaconID id);
    BeaconID find_child(BeaconID id);
    bool is_loop(BeaconID source_id, BeaconID target_id);
    unsigned int brightness_level(BeaconID id);
    std::vector<BeaconID> longest_parents(BeaconID id);
    void check_maxmin_brightness (BeaconID id);
    void update_total_color(BeaconID id);
    void modify_total_color(BeaconID id, Color new_color, Color old_color = NO_COLOR);
    BeaconID find_root_beacon(std::unordered_set<BeaconID> beacon_set);

};

#endif // DATASTRUCTURES_HH
