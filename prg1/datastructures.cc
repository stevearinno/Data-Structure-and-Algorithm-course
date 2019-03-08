// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <unordered_map>

#include <unordered_set>

#include <memory>

#include <algorithm>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this with your implementation
}

int Datastructures::beacon_count()
{
    // Replace this with your implementation
    return no_of_beacon;
}

void Datastructures::clear_beacons()
{
    // Replace this with your implementation
    BeaconDB.clear();
    no_of_beacon = 0;
}

std::vector<BeaconID> Datastructures::all_beacons()
{
//     Replace this with your implementation
    BeaconID to_be_pushed;
    std::vector<BeaconID> beacon_vector;
    std::unordered_map<BeaconID, std::shared_ptr<Beacon>>::const_iterator db_iterator
            = BeaconDB.begin();
    for (;db_iterator != BeaconDB.end(); db_iterator++)
    {
        to_be_pushed = db_iterator->first;
        beacon_vector.push_back(to_be_pushed);
    }

    return beacon_vector;
}

bool Datastructures::add_beacon(BeaconID id, const std::string& name, Coord xy, Color color)
{
    // Replace this with your implementation
    if (!find_id(id))           // if the beacon ID has been added
    {
        std::shared_ptr<Beacon> new_beacon = std::make_shared<Beacon>();

        new_beacon->id = id;
        new_beacon->name = name;
        new_beacon->coord = xy;
        new_beacon->color = color;

        BeaconDB[id] = new_beacon;
        no_of_beacon += 1;

        int bright_level = brightness_level(id);
        if ((min_bright_level == 0) || (bright_level < min_bright_level))
        {
            min_bright_level = bright_level;
            min_bright_beacon = id;
        }

        if ((max_bright_level == 0) || (bright_level > max_bright_level))
        {
            max_bright_level = bright_level;
            max_bright_beacon = id;
        }

        return true;
    }
    else
    {
        return false;
    }
}

std::string Datastructures::get_name(BeaconID id)
{
    // Replace this with your implementation
    if (find_id(id))
    {
        std::shared_ptr<Beacon> beacon_ptr = BeaconDB[id];
        return beacon_ptr->name;
    }
    else
    {
        return NO_NAME;
    }
}

Coord Datastructures::get_coordinates(BeaconID id)
{
    // Replace this with your implementation
    if (find_id(id))
    {
        std::shared_ptr<Beacon> beacon_ptr = BeaconDB[id];
        return beacon_ptr->coord;
    }
    else
    {
        return NO_COORD;
    }
}

Color Datastructures::get_color(BeaconID id)
{
    // Replace this with your implementation
    if (find_id(id))
    {
        std::shared_ptr<Beacon> beacon_ptr = BeaconDB[id];
        return beacon_ptr->color;
    }
    else
    {
        return NO_COLOR;
    }
}

std::vector<BeaconID> Datastructures::beacons_alphabetically()
{
    // Replace this with your implementation
    std::vector<std::tuple<std::string, BeaconID>> alpha_vector;

    std::unordered_map<BeaconID, std::shared_ptr<Beacon>>::const_iterator db_iterator
            = BeaconDB.begin();
    for (;db_iterator != BeaconDB.end(); db_iterator++)
    {
        BeaconID id = db_iterator->first;
        std::string name = get_name(id);
        alpha_vector.push_back(std::make_tuple(name, id));
    }
    std::sort(alpha_vector.begin(), alpha_vector.end());
    std::vector<BeaconID> alpha_sorted;
    unsigned int index = 0;
    while (index < alpha_vector.size())
    {
        alpha_sorted.push_back(std::get<1>(alpha_vector[index]));
        index++;
    }
    return alpha_sorted;

//    std::vector<BeaconID> alpha_vector = all_beacons();
//    std::sort(alpha_vector.begin(), alpha_vector.end(), [this](auto b1, auto b2)
//    { return get_name(b1) < get_name(b2) ;} );
//    return alpha_vector;
}

std::vector<BeaconID> Datastructures::beacons_brightness_increasing()
{
    // Replace this with your implementation
    std::vector<std::tuple<int, BeaconID>> brightness_vector;

    std::unordered_map<BeaconID, std::shared_ptr<Beacon>>::const_iterator db_iterator
            = BeaconDB.begin();
    for (;db_iterator != BeaconDB.end(); db_iterator++)
    {
        BeaconID id = db_iterator->first;
        int brightness = 3*get_color(id).r + 6*get_color(id).g + get_color(id).b;
        brightness_vector.push_back(std::make_tuple(brightness, id));
    }
    std::sort(brightness_vector.begin(), brightness_vector.end());
    std::vector<BeaconID> brightness_sorted;
    unsigned int index = 0;
    while (index < brightness_vector.size())
    {
        brightness_sorted.push_back(std::get<1>(brightness_vector[index]));
        index++;
    }


//    std::vector<BeaconID> brightness_vector = all_beacons();
//    std::sort(brightness_vector.begin(), brightness_vector.end(), [this](auto b1, auto b2)
//    { return 3*get_color(b1).r + 6*get_color(b1).g + get_color(b1).b
//                < 3*get_color(b2).r + 6*get_color(b2).g + get_color(b2).b ;} );
    return brightness_sorted;
}

BeaconID Datastructures::min_brightness()
{
    // Replace this with your implementation
    if (min_bright_beacon == NO_ID)
    {
        std::vector<BeaconID> brightness_vector = beacons_brightness_increasing();
        min_bright_beacon = brightness_vector[0];

    }

    return min_bright_beacon;
//    return NO_ID;
}

BeaconID Datastructures::max_brightness()
{
    // Replace this with your implementation
    if (max_bright_beacon == NO_ID)
    {
        std::vector<BeaconID> brightness_vector = beacons_brightness_increasing();
        max_bright_beacon = brightness_vector.back();
    }

    return max_bright_beacon;
//    return NO_ID;
}

std::vector<BeaconID> Datastructures::find_beacons(std::string const& name)
{
    // Replace this with your implementation
    std::vector<BeaconID> beaconID_vector;
    std::unordered_map<BeaconID, std::shared_ptr<Beacon>>::const_iterator db_iterator
            = BeaconDB.begin();
    for (;db_iterator != BeaconDB.end(); db_iterator++)
    {
        if (name == db_iterator->second->name)
        {
            beaconID_vector.push_back(db_iterator->first);
        }
    }
    std::sort(beaconID_vector.begin(),beaconID_vector.end());
    return beaconID_vector;
}

bool Datastructures::change_beacon_name(BeaconID id, const std::string& newname)
{
    // Replace this with your implementation
    if (find_id(id))
    {
        std::shared_ptr<Beacon> beacon_ptr = BeaconDB[id];
        beacon_ptr->name = newname;
        return true;
    }
    else
    {
        return false;
    }
}

bool Datastructures::change_beacon_color(BeaconID id, Color newcolor)
{
    // Replace this with your implementation
    if (find_id(id))
    {
        std::shared_ptr<Beacon> beacon_ptr= BeaconDB[id];
        beacon_ptr->color = newcolor;
        return true;
    }
    else
    {
        return false;
    }
}

bool Datastructures::add_lightbeam(BeaconID sourceid, BeaconID targetid)
{
    // Replace this with your implementation

    // SW - Needs to check more about the root (no circle)
    if (find_id(sourceid) && find_id(targetid)
            && (sourceid!=targetid)
            && (BeaconDB[sourceid]->child.size() == 0)
            && !is_loop(sourceid, targetid))
    {
        BeaconDB[sourceid]->child = targetid;
        BeaconDB[targetid]->parents.insert(sourceid);
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<BeaconID> Datastructures::get_lightsources(BeaconID id)
{
    // Replace this with your implementation
    if (find_id(id) && (BeaconDB[id]->parents.size() != 0 ))
    {
        std::vector<BeaconID> lightsources_vector;
        std::unordered_set<BeaconID> lightsources_set;
        lightsources_set = BeaconDB[id]->parents;
        std::unordered_set<BeaconID>::const_iterator set_iterator
                = lightsources_set.begin();
        for(; set_iterator != lightsources_set.end(); set_iterator++)
        {
            lightsources_vector.push_back(BeaconDB[*set_iterator]->id);
        }
        std::sort(lightsources_vector.begin(), lightsources_vector.end());
        return lightsources_vector;
    }
    else
    {
        return {{NO_ID}};
    }

}


std::vector<BeaconID> Datastructures::path_outbeam(BeaconID id)
{
    // Replace this with your implementation
    if (find_id(id))
    {
        std::vector<BeaconID> child_vector;
        BeaconID child;
        while (child != NO_ID)
        {
            child_vector.push_back(id);
            child = find_child(id);
            id = child;
        }
        return child_vector;
    }
    else
    {
        return {{NO_ID}};
    }

}

bool Datastructures::remove_beacon(BeaconID /*id*/)
{
    // Replace this with your implementation
    return false;
}

std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID /*id*/)
{
    // Replace this with your implementation
    return {{NO_ID}};
}

Color Datastructures::total_color(BeaconID /*id*/)
{
    // Replace this with your implementation
    return NO_COLOR;
}

bool Datastructures::find_id(BeaconID id)
{
    if (BeaconDB.find(id) == BeaconDB.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

BeaconID Datastructures::find_child(BeaconID id)
{
    if (BeaconDB[id]->child.size() != 0)
    {
        return BeaconDB[id]->child;
    }
    else
    {
        return NO_ID;
    }
}

bool Datastructures::is_loop(BeaconID source_id, BeaconID target_id)
{
    std::vector<BeaconID> all_children = path_outbeam(target_id);

    if(std::find(all_children.begin(), all_children.end(), source_id) != all_children.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Datastructures::brightness_level(BeaconID id)
{
    int red = BeaconDB[id]->color.r;
    int green = BeaconDB[id]->color.g;
    int blue = BeaconDB[id]->color.b;
    int level = 3*red + 6*green + blue;

    return level;
}

//std::unordered_set<BeaconID> Datastructures::find_roots(BeaconID id)
//{
//    std::unordered_set<BeaconID> parents_set;
//    if (BeaconDB[id]->parents.size() == 0)
//    {
//        parents_set.insert(id);
//    }
//    else
//    {
//        std::unordered_set<BeaconID> parent_set = BeaconDB[id]->parents;
//        std::unordered_set<BeaconID>::const_iterator set_iterator = parent_set.begin();
//        for(; set_iterator != parent_set.end(); set_iterator++)
//        {
//            find_roots(*set_iterator);
//        }
//    }
//    return parents_set;
//}






