// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <unordered_map>

#include <unordered_set>

#include <map>

#include <memory>

#include <algorithm>

#include <queue>

#include <QDebug>

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
        new_beacon->sum_color = color;

        BeaconDB[id] = new_beacon;
        no_of_beacon += 1;

        check_maxmin_brightness(id);

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

        std::multimap<std::string, BeaconID> alpha_map;

        std::unordered_map<BeaconID, std::shared_ptr<Beacon>>::const_iterator db_iterator
                = BeaconDB.begin();
        for (;db_iterator != BeaconDB.end(); db_iterator++)
        {
            BeaconID id = db_iterator->first;
            std::string name = get_name(id);
            alpha_map.insert(std::pair<std::string, BeaconID>(name,id));
        }

        std::vector<BeaconID> alpha_vector;
        std::multimap<std::string, BeaconID>::const_iterator map_iterator
                = alpha_map.begin();
        for (;map_iterator != alpha_map.end(); map_iterator++)
        {
            alpha_vector.push_back(map_iterator->second);
        }
        return alpha_vector;
}

std::vector<BeaconID> Datastructures::beacons_brightness_increasing()
{
    // Replace this with your implementation
    std::multimap<int, BeaconID> brightness_map;

    std::unordered_map<BeaconID, std::shared_ptr<Beacon>>::const_iterator db_iterator
            = BeaconDB.begin();
    for (;db_iterator != BeaconDB.end(); db_iterator++)
    {
        BeaconID id = db_iterator->first;
        int level = brightness_level(id);
        brightness_map.insert(std::pair<int, BeaconID>(level,id));
    }

    std::vector<BeaconID> brightness_vector;
    std::multimap<int, BeaconID>::const_iterator map_iterator
            = brightness_map.begin();
    for (;map_iterator != brightness_map.end(); map_iterator++)
    {
        brightness_vector.push_back(map_iterator->second);
    }

    return brightness_vector;
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
        Color oldcolor = beacon_ptr->color;
        beacon_ptr->color = newcolor;
        modify_total_color(id, newcolor, oldcolor);
        check_maxmin_brightness(id);
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

    if (find_id(sourceid) && find_id(targetid)
            && (sourceid!=targetid)
            && (BeaconDB[sourceid]->child == NO_ID)
            && !is_loop(sourceid, targetid))
    {
        BeaconDB[sourceid]->child = targetid;
        BeaconDB[targetid]->parents.insert(sourceid);
        BeaconDB[targetid]->no_of_parents++;

        Color transmitted_color;
        transmitted_color.r = BeaconDB[sourceid]->sum_color.r/
                (BeaconDB[sourceid]->no_of_parents+1);
        transmitted_color.g = BeaconDB[sourceid]->sum_color.g/
                (BeaconDB[sourceid]->no_of_parents+1);
        transmitted_color.b = BeaconDB[sourceid]->sum_color.b/
                (BeaconDB[sourceid]->no_of_parents+1);
        modify_total_color(targetid, transmitted_color);
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
    if (find_id(id))
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

bool Datastructures::remove_beacon(BeaconID id)
{
    // Replace this with your implementation
    if (find_id(id))
    {
        if (BeaconDB[id]->child != NO_ID)
        {
            update_total_color(id);
            BeaconID child_id = find_child(id);
            BeaconDB[child_id]->no_of_parents--;
            BeaconDB[child_id]->parents.erase(id);

        }
        if (BeaconDB[id]->parents.size() != 0)
        {
            std::unordered_set<BeaconID> parents_id = BeaconDB[id]->parents;
            std::unordered_set<BeaconID>::const_iterator set_iterator = parents_id.begin();
            for(;set_iterator != parents_id.end(); set_iterator++)
            {
                BeaconDB[*set_iterator]->child = NO_ID;
            }
        }
        if (min_bright_beacon == id)
        {
            min_bright_beacon = NO_ID;
            min_bright_level = 0;
            min_brightness();
        }
        if (max_bright_beacon == id)
        {
            max_bright_beacon = NO_ID;
            max_bright_level = 0;
            max_brightness();
        }

        BeaconDB.erase(id);
        no_of_beacon--;
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID id)
{
    // Replace this with your implementation
    if (find_id(id))
    {
//        return longest_parents(id);
        std::unordered_set<BeaconID> id_set;
        id_set.insert(id);
        BeaconID parent_beacon = find_root_beacon(id_set);
        std::vector<BeaconID> route_vector;
        BeaconID child;
        while (child != id && parent_beacon != id)
        {
            route_vector.push_back(parent_beacon);
            child = find_child(parent_beacon);
            parent_beacon = child;
        }
        route_vector.push_back(id);
        return route_vector;
    }
    else
    {
        return {{NO_ID}};
    }
}

Color Datastructures::total_color(BeaconID id)
{
    // Replace this with your implementation
    if (find_id(id))
    {
        Color sum_color = BeaconDB[id]->sum_color;
        int sum_beacons = BeaconDB[id]->no_of_parents + 1;

        Color color_fin;

        color_fin.r = sum_color.r/sum_beacons;
        color_fin.g = sum_color.g/sum_beacons;
        color_fin.b = sum_color.b/sum_beacons;

        return color_fin;

    }
    else
    {
        return NO_COLOR;
    }
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
    if (BeaconDB[id]->child != NO_ID)
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

unsigned int Datastructures::brightness_level(BeaconID id)
{
    unsigned int red = BeaconDB[id]->color.r;
    unsigned int green = BeaconDB[id]->color.g;
    unsigned int blue = BeaconDB[id]->color.b;
    unsigned int level = 3*red + 6*green + blue;

    return level;
}

std::vector<BeaconID> Datastructures::longest_parents(BeaconID id)
{
    std::vector<BeaconID> parents_vector;
    if (BeaconDB[id]->parents.size() != 0)
    {
        std::unordered_set<BeaconID> parents_id = BeaconDB[id]->parents;
        std::unordered_set<BeaconID>::const_iterator set_iterator = parents_id.begin();
        for(;set_iterator != parents_id.end(); set_iterator++)
        {
            parents_vector.push_back(*set_iterator);
            longest_parents(*set_iterator);
        }
    }
    else
    {
        parents_vector.push_back(id);
    }
    return parents_vector;
}

void Datastructures::check_maxmin_brightness(BeaconID id)
{
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
}

void Datastructures::update_total_color(BeaconID id)
{
    Color sum_color = BeaconDB[id]->sum_color;
    // This is for the case of remove beacon
    BeaconID child = BeaconDB[id]->child;
    if (child != NO_ID)
    {

        Color old_sum_color_child = BeaconDB[child]->sum_color;
        Color transmitted_color;
        transmitted_color.r = sum_color.r/(BeaconDB[id]->no_of_parents+1);
        transmitted_color.g = sum_color.g/(BeaconDB[id]->no_of_parents+1);
        transmitted_color.b = sum_color.b/(BeaconDB[id]->no_of_parents+1);

        Color new_sum_color_child;
        new_sum_color_child.r = old_sum_color_child.r - transmitted_color.r;
        new_sum_color_child.g = old_sum_color_child.g - transmitted_color.g;
        new_sum_color_child.b = old_sum_color_child.b - transmitted_color.b;

        BeaconDB[child]->sum_color = new_sum_color_child;
        update_total_color(child);
    }
}

void Datastructures::modify_total_color(BeaconID id, Color new_color, Color old_color)
{
    Color old_sum_color = BeaconDB[id]->sum_color;

//    int no_of_parents = BeaconDB[id]->no_of_parents;

    // This is for the case of add_lightbeam
    if (old_color == NO_COLOR)
    {
        Color older_color;
        older_color.r = old_sum_color.r/(BeaconDB[id]->no_of_parents+1);
        older_color.g = old_sum_color.g/(BeaconDB[id]->no_of_parents+1);
        older_color.b = old_sum_color.b/(BeaconDB[id]->no_of_parents+1);

        Color new_received_color = new_color;
        Color new_sum_color;
        new_sum_color.r = old_sum_color.r + new_received_color.r;
        new_sum_color.g = old_sum_color.g + new_received_color.g;
        new_sum_color.b = old_sum_color.b + new_received_color.b;

        BeaconDB[id]->sum_color = new_sum_color;

        if (BeaconDB[id]->child != NO_ID)
        {
            Color transmitted_color;
            transmitted_color.r = new_sum_color.r/(BeaconDB[id]->no_of_parents+1);
            transmitted_color.g = new_sum_color.g/(BeaconDB[id]->no_of_parents+1);
            transmitted_color.b = new_sum_color.b/(BeaconDB[id]->no_of_parents+1);
            modify_total_color(BeaconDB[id]->child, transmitted_color, older_color);
        }
    }
    // This is for the case of change_color
    else
    {
        Color new_sum_color;
        new_sum_color.r = old_sum_color.r - old_color.r + new_color.r;
        new_sum_color.g = old_sum_color.g - old_color.g + new_color.g;
        new_sum_color.b = old_sum_color.b - old_color.b + new_color.b;

        Color old_transmitted_color;
        old_transmitted_color.r = old_sum_color.r/(BeaconDB[id]->no_of_parents+1);
        old_transmitted_color.g = old_sum_color.g/(BeaconDB[id]->no_of_parents+1);
        old_transmitted_color.b = old_sum_color.b/(BeaconDB[id]->no_of_parents+1);

        BeaconDB[id]->sum_color = new_sum_color;

        if (BeaconDB[id]->child != NO_ID)
        {
            Color new_transmitted_color;
            new_transmitted_color.r = new_sum_color.r/(BeaconDB[id]->no_of_parents+1);
            new_transmitted_color.g = new_sum_color.g/(BeaconDB[id]->no_of_parents+1);
            new_transmitted_color.b = new_sum_color.b/(BeaconDB[id]->no_of_parents+1);
            modify_total_color(BeaconDB[id]->child, new_transmitted_color, old_transmitted_color);
        }
    }
}

BeaconID Datastructures::find_root_beacon(std::unordered_set<BeaconID> beacon_set)
{
    std::unordered_set<BeaconID> parents_set;
    std::unordered_set<BeaconID>::const_iterator set_iterator = beacon_set.begin();
    std::unordered_set<BeaconID> fin_parent_set;
    for (; set_iterator != beacon_set.end(); set_iterator++)
    {
        set_union(std::begin(parents_set), std::end(parents_set),
                      std::begin(BeaconDB[*set_iterator]->parents),
                std::end(BeaconDB[*set_iterator]->parents),
                std::inserter(fin_parent_set, std::begin(fin_parent_set)));
    }
    if (fin_parent_set.size() != 0)
    {
        return find_root_beacon(fin_parent_set);
    }
    else
    {
        return *beacon_set.begin();
    }
}

