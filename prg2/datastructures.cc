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

#include <set>

#include <stack>

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
            BeaconID child_id = find_child(id);
            BeaconDB[child_id]->no_of_parents--;
            BeaconDB[child_id]->parents.erase(id);
            update_total_color(id);
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

        Color old_color_child;
        old_color_child.r = old_sum_color_child.r/(BeaconDB[child]->no_of_parents+2);
        old_color_child.g = old_sum_color_child.g/(BeaconDB[child]->no_of_parents+2);
        old_color_child.b = old_sum_color_child.b/(BeaconDB[child]->no_of_parents+2);

        Color new_color_child;
        new_color_child.r = new_sum_color_child.r/(BeaconDB[child]->no_of_parents+1);
        new_color_child.g = new_sum_color_child.g/(BeaconDB[child]->no_of_parents+1);
        new_color_child.b = new_sum_color_child.b/(BeaconDB[child]->no_of_parents+1);
        BeaconDB[child]->sum_color = new_sum_color_child;
        if (BeaconDB[child]->child != NO_ID)
        {
            modify_total_color(BeaconDB[child]->child, new_color_child, old_color_child);
        }
//        update_total_color(child);
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
        older_color.r = old_sum_color.r/(BeaconDB[id]->no_of_parents);
        older_color.g = old_sum_color.g/(BeaconDB[id]->no_of_parents);
        older_color.b = old_sum_color.b/(BeaconDB[id]->no_of_parents);

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

std::vector<Coord> Datastructures::all_xpoints()
{
    // Replace this with your implementation
    std::vector<Coord> xpoints_vector;
//            std::unordered_map<Coord, std::shared_ptr<Xpoint>, CoordHash>::const_iterator map_iterator = XpointDB.begin();
            std::map<Coord, std::shared_ptr<Xpoint>>::const_iterator map_iterator = XpointDB.begin();
            for(; map_iterator != XpointDB.end(); map_iterator++)
            {
                xpoints_vector.push_back(map_iterator->first);
            }

    return xpoints_vector;
}

bool Datastructures::add_fibre(Coord xpoint1, Coord xpoint2, Cost cost)
{
    // Replace this with your implementation
    if (!find_xconnection(xpoint1, xpoint2)){
        std::shared_ptr<Xpoint> new_xpoint1;
        std::shared_ptr<Xpoint> new_xpoint2;

        if (!find_xpoint(xpoint1))
        {
            new_xpoint1 = std::make_shared<Xpoint>();
            new_xpoint1->coord = xpoint1;
        }
        else
        {
            new_xpoint1 = XpointDB[xpoint1];
        }

        if (!find_xpoint(xpoint2))
        {
            new_xpoint2 = std::make_shared<Xpoint>();
            new_xpoint2->coord = xpoint2;
        }
        else
        {
            new_xpoint2 = XpointDB[xpoint2];
        }

        std::shared_ptr<Edge> new_edge1 = std::make_shared<Edge>();
        std::shared_ptr<Edge> new_edge2 = std::make_shared<Edge>();
        new_edge1->target = new_xpoint2;
        new_edge2->target = new_xpoint1;
        new_edge1->cost = cost;
        new_edge2->cost = cost;

        new_xpoint1->edges.insert(new_edge1);
        new_xpoint2->edges.insert(new_edge2);

        XpointDB[xpoint1] = new_xpoint1;
        XpointDB[xpoint2] = new_xpoint2;

//        qDebug() << "edge list1";
//        std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator = new_xpoint1->edges.begin();
//        for(; set_iterator != new_xpoint1->edges.end(); set_iterator++)
//        {
//            std::shared_ptr<Edge> edge1 = *set_iterator;
//            qDebug() << edge1->target->coord.x;
//            qDebug() << edge1->target->coord.y;
//            qDebug() << "---";
//        }

//        qDebug() << "edge list2";
//        std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator2 = new_xpoint2->edges.begin();
//        for(; set_iterator2 != new_xpoint2->edges.end(); set_iterator2++)
//        {
//            std::shared_ptr<Edge> edge2 = *set_iterator2;
//            qDebug() << edge2->target->coord.x;
//            qDebug() << edge2->target->coord.y;
//            qDebug() << "---";
//        }

        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::pair<Coord, Cost> > Datastructures::get_fibres_from(Coord xpoint)
{
    // Replace this with your implementation
    if (find_xpoint(xpoint))
    {
        std::vector<std::pair<Coord, Cost>> edge_vector;
        std::shared_ptr<Xpoint> xnode = XpointDB[xpoint];
        std::unordered_set<std::shared_ptr<Edge>> edge_set = xnode->edges;
        std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator = edge_set.begin();
        for(; set_iterator != edge_set.end(); set_iterator++)
        {
            std::shared_ptr<Edge> edge1 = *set_iterator;
            edge_vector.push_back(std::make_pair(edge1->target->coord, edge1->cost));
        }
        sort(edge_vector.begin(),edge_vector.end());
        return edge_vector;
    }
    else
    {
        return {};
    }
}

std::vector<std::pair<Coord, Coord> > Datastructures::all_fibres()
{
    // Replace this with your implementation
    if (XpointDB.size()!=0)
    {

        std::vector<std::pair<Coord, Coord> > fibre_vector;
        std::map<Coord, std::shared_ptr<Xpoint>>::const_iterator map_iterator = XpointDB.begin();
        for(; map_iterator != XpointDB.end(); map_iterator++)
        {
            std::set<Coord> coord_set;
            std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator = map_iterator->second->edges.begin();
            for(; set_iterator != map_iterator->second->edges.end(); set_iterator++)
            {
                std::shared_ptr<Edge> edge1 = *set_iterator;
                if (operator<(map_iterator->first, edge1->target->coord))
                {
                    coord_set.insert(edge1->target->coord);
                }
            }
            std::set<Coord>::const_iterator coord_iterator = coord_set.begin();
            for(; coord_iterator != coord_set.end(); coord_iterator++)
            {
                fibre_vector.push_back(std::make_pair(map_iterator->first, *coord_iterator));
            }
        }
        return fibre_vector;
    }
    else
    {
        return {};
    }
}

bool Datastructures::remove_fibre(Coord xpoint1, Coord xpoint2)
{
    // Replace this with your implementation
    if (find_xconnection(xpoint1, xpoint2))
    {
        remove_subfibre(xpoint1, xpoint2);
        remove_subfibre(xpoint2, xpoint1);
        return true;
    }
    else
    {
        return false;
    }

}

void Datastructures::clear_fibres()
{
    // Replace this with your implementation
//    std::unordered_map<Coord, std::shared_ptr<Xpoint>, CoordHash>::const_iterator db_iterator = XpointDB.begin();
    std::map<Coord, std::shared_ptr<Xpoint>>::const_iterator db_iterator = XpointDB.begin();
    for(; db_iterator != XpointDB.end(); db_iterator++)
    {
//        std::unordered_set<std::shared_ptr<Edge>> edge_set = db_iterator->second->edges;
        std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator = db_iterator->second->edges.begin();
        for(; set_iterator != db_iterator->second->edges.end(); set_iterator++)
        {
            std::shared_ptr<Edge> edge_element = *set_iterator;
            edge_element->target = nullptr;
        }
        db_iterator->second->edges.clear();
    }
    XpointDB.clear();

}

std::vector<std::pair<Coord, Cost> > Datastructures::route_any(Coord fromxpoint, Coord toxpoint)
{
    // Replace this with your implementation
    std::shared_ptr<Xpoint> origin_pt = XpointDB[fromxpoint];
    std::shared_ptr<Xpoint> destination_pt = XpointDB[toxpoint];

    if (origin_pt == destination_pt)
    {
        return {std::make_pair(origin_pt->coord, 0)};
    }
    else if (find_any_path(origin_pt, destination_pt))
    {
        qDebug() << "masuk pak Eko!";
        return final_path(origin_pt, destination_pt);
    }
    else
    {
        return {};
    }
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_least_xpoints(Coord fromxpoint, Coord toxpoint)
{
    // Replace this with your implementation
    std::shared_ptr<Xpoint> origin_pt = XpointDB[fromxpoint];
    std::shared_ptr<Xpoint> destination_pt = XpointDB[toxpoint];

    if (origin_pt == destination_pt)
    {
        return {std::make_pair(origin_pt->coord, 0)};
    }
    else
    {
        if (find_any_path(origin_pt, destination_pt))
        {
            return final_path(origin_pt, destination_pt);
        }
    }
    return {};
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_fastest(Coord fromxpoint, Coord toxpoint)
{
    // Replace this with your implementation
    std::shared_ptr<Xpoint> origin_pt = XpointDB[fromxpoint];
    std::shared_ptr<Xpoint> destination_pt = XpointDB[toxpoint];

    if (origin_pt == destination_pt)
    {
        return {std::make_pair(origin_pt->coord, 0)};
    }
    else
    {
        if (find_fastest_path(origin_pt, destination_pt))
        {
            return final_path(origin_pt, destination_pt);
        }
    }

    return {};
}

std::vector<Coord> Datastructures::route_fibre_cycle(Coord startxpoint)
{
    // Replace this with your implementation
    std::shared_ptr<Xpoint> origin_pt = XpointDB[startxpoint];
    std::pair<std::shared_ptr<Xpoint>, std::shared_ptr<Xpoint>> pair_pt = find_cycle(origin_pt);
//    qDebug() << pair_pt.first->coord.x;
//    qDebug() << pair_pt.first->coord.y;
//    qDebug() << "---";
//    qDebug() << pair_pt.second->coord.x;
//    qDebug() << pair_pt.second->coord.y;
//    bool kondisi = find_any_path(pair_pt.first, pair_pt.second);
//    std::vector<Coord> test_vector = cycle_path(origin_pt, last_pt);
//    std::vector<std::pair<Coord, Cost> > test2_vector = final_path(origin_pt, last_pt);

    if ((pair_pt.first != nullptr) && (pair_pt.second != nullptr))
    {
        return cycle_path(pair_pt.first, pair_pt.second);
    }
    else
    {
        return {};
    }
}

Cost Datastructures::trim_fibre_network()
{
    // Replace this with your implementation
    std::vector<Coord> xpoints_vec = all_xpoints();
    std::vector<std::pair<Coord, Coord>> fibres_vec = all_fibres();
    std::vector<std::shared_ptr<Xpoint>> xpoints_pts;

    int vec_size = xpoints_vec.size();
    for(int index = 0; index<vec_size; index++)
    {
        xpoints_pts.push_back(XpointDB[xpoints_vec[index]]);
    }

    std::vector<std::shared_ptr<Xpoint>> destination_vec(xpoints_pts.begin()+1,
                                                         xpoints_pts.end());
    recursive_update_dist(xpoints_pts[0], destination_vec);

    int fibres_size = fibres_vec.size();
    for(int index = 0; index<fibres_size; index++)
    {
        if (std::find(valid_fibres.begin(), valid_fibres.end(),
                      fibres_vec[index]) == valid_fibres.end())
        {
            remove_fibre(fibres_vec[index].first, fibres_vec[index].second);
        }
    }

    std::vector<std::pair<Coord, Coord>> new_fibres_vec = all_fibres();
    int new_vec_size = new_fibres_vec.size();
    int total_cost = 0;
    for(int index = 0; index<new_vec_size; index++)
    {
        total_cost = total_cost + fibre_cost(new_fibres_vec[index]);
    }

    return total_cost;
}

bool Datastructures::find_xconnection(Coord xpoint1, Coord xpoint2)
{
    if (!find_xpoint(xpoint1) || !find_xpoint(xpoint2))
    {
        return false;
    }
    else
    {
//        std::unordered_set<std::shared_ptr<Edge>> edge_list = XpointDB[xpoint1]->edges;
        std::unordered_set<std::shared_ptr<Edge>>::iterator db_iterator = XpointDB[xpoint1]->edges.begin();
        for (;db_iterator != XpointDB[xpoint1]->edges.end(); db_iterator++)
        {
            std::shared_ptr<Edge> edge_element = *db_iterator;
            if (operator==(edge_element->target->coord, XpointDB[xpoint2]->coord))
            {
                return true;
            }
        }
        return false;
    }
}

bool Datastructures::find_xpoint(Coord xpoint)
{
    if (XpointDB.find(xpoint) == XpointDB.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Datastructures::remove_subfibre(Coord xpoint1, Coord xpoint2)
{
    std::unordered_set<std::shared_ptr<Edge>>::iterator db_iterator = XpointDB[xpoint1]->edges.begin();
    for (;db_iterator != XpointDB[xpoint1]->edges.end(); db_iterator++)
    {
        std::shared_ptr<Edge> edge_element = *db_iterator;
        if (operator==(edge_element->target->coord, XpointDB[xpoint2]->coord))
        {
            XpointDB[xpoint1]->edges.erase(edge_element);
            return;
        }
    }
}

bool Datastructures::find_any_path(std::shared_ptr<Xpoint> origin_pt, std::shared_ptr<Xpoint> destination_pt)
{
    std::queue<std::shared_ptr<Xpoint>> todo;
    origin_pt->dist = 0;
    marked_xpoints.push_back(origin_pt);
    todo.push(origin_pt);    
    while (!todo.empty()){
        std::shared_ptr<Xpoint> current_pt = todo.front();
        todo.pop();
        std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator = current_pt->edges.begin();
        for(; set_iterator != current_pt->edges.end(); set_iterator++)
        {
            std::shared_ptr<Edge> current_eg = *set_iterator;
            std::shared_ptr<Xpoint> next_pt = current_eg->target;
            if ((next_pt->dist == -1) && (!next_pt->isProcessed))
            {
                next_pt->dist = current_pt->dist + current_eg->cost;
                next_pt->prev = current_pt;
                marked_xpoints.push_back(next_pt);
                if (next_pt == destination_pt)
                {
                    return true;
                }
                todo.push(next_pt);
            }
        }
        current_pt->isProcessed = true;
    }
    reset_marked_xpoints();
    return false;
}

bool Datastructures::find_fastest_path(std::shared_ptr<Xpoint> origin_pt, std::shared_ptr<Xpoint> destination_pt)
{
    typedef std::pair<Cost, std::shared_ptr<Xpoint>> cost_pair;
    bool isFound = false;
    needUpdate = false;
    std::priority_queue<cost_pair, std::vector<cost_pair>, std::greater<cost_pair>> priority_q;
    origin_pt->dist = 0;
    marked_xpoints.push_back(origin_pt);
    priority_q.push(std::make_pair(0, origin_pt));

    while (!priority_q.empty())
    {
        std::shared_ptr<Xpoint> current_pt = priority_q.top().second;
        priority_q.pop();
        if (current_pt->isProcessed == false)
        {
            std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator = current_pt->edges.begin();
            for(; set_iterator != current_pt->edges.end(); set_iterator++)
            {
                std::shared_ptr<Edge> current_eg = *set_iterator;
                std::shared_ptr<Xpoint> next_pt = current_eg->target;
                if ((next_pt->dist == -1) && (!next_pt->isProcessed))
                {
                    if (next_pt == destination_pt)
                    {
                        isFound = true;
                    }
                    priority_q.push(std::make_pair((current_pt->dist + current_eg->cost), next_pt));
                }
                relax(current_pt, next_pt, current_eg->cost);
                if (needUpdate)
                {
                    priority_q.push(std::make_pair((current_pt->dist + current_eg->cost), next_pt));
                }
            }
            current_pt->isProcessed = true;
        }

    }
    return isFound;
}

void Datastructures::relax(std::shared_ptr<Xpoint> current_pt, std::shared_ptr<Xpoint> next_pt, Cost cost)
{
    if ((next_pt->dist == -1) || (next_pt->dist > (current_pt->dist + cost)))
    {
        next_pt->dist = current_pt->dist + cost;
        next_pt->prev = current_pt;
//        next_pt->isTrimmed = true;
        needUpdate = true;

        marked_xpoints.push_back(next_pt);        
    }
}

std::pair<std::shared_ptr<Xpoint>, std::shared_ptr<Xpoint>> Datastructures::find_cycle(std::shared_ptr<Xpoint> origin_pt)
{
    std::stack<std::shared_ptr<Xpoint>> xpoint_stack;

    xpoint_stack.push(origin_pt);
    while (!xpoint_stack.empty())
    {
        std::shared_ptr<Xpoint> current_pt = xpoint_stack.top();
        xpoint_stack.pop();
        if ((current_pt->dist == -1) && (!current_pt->isProcessed))
        {
            current_pt->dist = 0;
            marked_xpoints.push_back(current_pt);
            xpoint_stack.push(current_pt);
            std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator = current_pt->edges.begin();
            for(; set_iterator != current_pt->edges.end(); set_iterator++)
            {
                std::shared_ptr<Edge> current_eg = *set_iterator;
                std::shared_ptr<Xpoint> next_pt = current_eg->target;

                if ((next_pt->dist == -1) && (!next_pt->isProcessed))
                {
                    xpoint_stack.push(next_pt);
                    next_pt->prev = current_pt;
                    marked_xpoints.push_back(next_pt);
//                    qDebug() << "white pt";
//                    qDebug() << current_pt->coord.x;
//                    qDebug() << current_pt->coord.y;
//                    qDebug() << next_pt->coord.x;
//                    qDebug() << next_pt->coord.y;
//                    qDebug() << "end white pt";
                }
//                qDebug() << "general (next_pt)";
//                qDebug() << next_pt->coord.x;
//                qDebug() << next_pt->coord.y;
//                qDebug() << next_pt->dist;
//                qDebug() << next_pt->isProcessed;
//                qDebug() << "end general";
                if ((next_pt->dist == 0) && (!next_pt->isProcessed)&& (next_pt != current_pt->prev))
                    //  && (next_pt != current_pt->prev)
                {
                    // this is what we are looking for
                    qDebug() << current_pt->coord.x;
                    qDebug() << current_pt->coord.y;
                    qDebug() << next_pt->coord.x;
                    qDebug() << next_pt->coord.y;
                    return std::make_pair(next_pt, current_pt);
                }
            }
        }
        else
        {
            current_pt->isProcessed = true;
            marked_xpoints.push_back(current_pt);
        }

    }
    reset_marked_xpoints();
    return {nullptr, nullptr};
}

std::vector<std::pair<Coord, Cost> > Datastructures::final_path(std::shared_ptr<Xpoint> origin_pt, std::shared_ptr<Xpoint> destination_pt)
{
    std::vector<std::pair<Coord, Cost>> route_vector;
    std::shared_ptr<Xpoint> current_pt = destination_pt;
    route_vector.insert(route_vector.begin(), std::make_pair(current_pt->coord, current_pt->dist));
    current_pt->dist = -1;
    current_pt->isProcessed = false;
    while (current_pt != origin_pt)
    {
        std::shared_ptr<Xpoint> temp_pt = current_pt;
        current_pt = temp_pt->prev;
        temp_pt->prev = nullptr;
        route_vector.insert(route_vector.begin(), std::make_pair(current_pt->coord, current_pt->dist));
        current_pt->dist = -1;
        current_pt->isProcessed = false;
    }
    reset_marked_xpoints();
    return route_vector;
}

std::vector<Coord > Datastructures::cycle_path(std::shared_ptr<Xpoint> origin_pt, std::shared_ptr<Xpoint> destination_pt)
{
    std::vector<Coord> coord_vector;
    std::shared_ptr<Xpoint> current_pt = destination_pt;
    coord_vector.insert(coord_vector.begin(), origin_pt->coord);
    coord_vector.insert(coord_vector.begin(), current_pt->coord);
    current_pt->dist = -1;
    current_pt->isProcessed = false;
    while (current_pt != origin_pt)
    {
        std::shared_ptr<Xpoint> temp_pt = current_pt;
        current_pt = temp_pt->prev;
        temp_pt->prev = nullptr;
        coord_vector.insert(coord_vector.begin(), current_pt->coord);
        current_pt->dist = -1;
        current_pt->isProcessed = false;
    }
    reset_marked_xpoints();
    return coord_vector;
}

void Datastructures::reset_marked_xpoints()
{
    std::vector<std::shared_ptr<Xpoint>>::const_iterator vector_iterator = marked_xpoints.begin();
    for(; vector_iterator != marked_xpoints.end(); vector_iterator++)
    {
        std::shared_ptr<Xpoint> current_xpoint = *vector_iterator;
        current_xpoint->dist = -1;
        current_xpoint->prev = nullptr;
        current_xpoint->isProcessed = false;
        current_xpoint->isTrimmed = false;
    }
    marked_xpoints.clear();
}

void Datastructures::recursive_update_dist(std::shared_ptr<Xpoint> origin_pt, std::vector<std::shared_ptr<Xpoint> > destination_vec)
{
    int vec_size = destination_vec.size();
    for(int index = 0; index < vec_size; index++)
    {
        find_fastest_path(origin_pt, destination_vec[index]);
        qDebug() << "Done here1";
        final_path2(origin_pt, destination_vec[index]);
        qDebug() << "Done here2";
    }

    if (vec_size > 1)
    {
        std::vector<std::shared_ptr<Xpoint>> new_dest_vec(destination_vec.begin()+1, destination_vec.end());
        recursive_update_dist(destination_vec[0], new_dest_vec);
    }
    else
    {
        return;
    }
}

void Datastructures::final_path2(std::shared_ptr<Xpoint> origin_pt, std::shared_ptr<Xpoint> destination_pt)
{
    std::set<std::pair<Coord, Coord>> fibre_set;
    qDebug() << "satu";
    std::shared_ptr<Xpoint> current_pt = destination_pt;

    if (current_pt->prev != nullptr)
    {
        qDebug() << "dua";
        Coord coord3 = current_pt->coord;
        qDebug() << "tiga";
        Coord coord4 = current_pt->prev->coord;
        qDebug() << "dari";
        qDebug() << coord3.x;
        qDebug() << coord3.y;
        qDebug() << "ke";
        qDebug() << coord4.x;
        qDebug() << coord4.y;
        qDebug() << "selesai";
        if (operator<(coord3, coord4))
        {
            fibre_set.insert(std::make_pair(coord3, coord4));
        }
        else
        {
            fibre_set.insert(std::make_pair(coord4, coord3));
        }
    }

    current_pt->dist = -1;
    current_pt->isProcessed = false;
    while ((current_pt != origin_pt) && (current_pt->prev != nullptr))
    {
        std::shared_ptr<Xpoint> temp_pt = current_pt;
        current_pt = temp_pt->prev;
        temp_pt->prev = nullptr;
        std::shared_ptr<Xpoint> test_ptr = current_pt->prev;
        if (current_pt->prev != nullptr)
        {
            Coord coord1 = current_pt->coord;
            Coord coord2 = current_pt->prev->coord;
//            qDebug() << "dari";
//            qDebug() << coord1.x;
//            qDebug() << coord1.y;
//            qDebug() << "ke";
//            qDebug() << coord2.x;
//            qDebug() << coord2.y;
//            qDebug() << "selesai";
            if (operator<(coord1, coord2))
            {
                fibre_set.insert(std::make_pair(coord1, coord2));
            }
            else
            {
                fibre_set.insert(std::make_pair(coord2, coord1));
            }
        }
        current_pt->dist = -1;
        current_pt->isProcessed = false;
    }
    std::set<std::pair<Coord, Coord>>::const_iterator set_iterator = fibre_set.begin();
    for (; set_iterator != fibre_set.end(); set_iterator++)
    {
        valid_fibres.push_back(*set_iterator);
    }
    reset_marked_xpoints();
}

Cost Datastructures::fibre_cost(std::pair<Coord, Coord> fibre_pair)
{
    std::shared_ptr<Xpoint> xpoint1 = XpointDB[fibre_pair.first];
    std::shared_ptr<Xpoint> xpoint2 = XpointDB[fibre_pair.second];

//    std::unordered_set<std::shared_ptr<Edge>> edges_set = xpoint1->edges;
    std::unordered_set<std::shared_ptr<Edge>>::const_iterator set_iterator =
            xpoint1->edges.begin();
    for (; set_iterator != xpoint1->edges.end(); set_iterator++)
    {
        std::shared_ptr<Edge> edge_target = *set_iterator;
        std::shared_ptr<Xpoint> xtarget = edge_target->target;
        if (xtarget == xpoint2)
        {
            return edge_target->cost;
        }
    }
}
