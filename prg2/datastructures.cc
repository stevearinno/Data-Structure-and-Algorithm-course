// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

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
    return NO_VALUE;
}

void Datastructures::clear_beacons()
{
    // Replace this with your implementation
}

std::vector<BeaconID> Datastructures::all_beacons()
{
    // Replace this with your implementation
    return {};
}

bool Datastructures::add_beacon(BeaconID /*id*/, const std::string& /*name*/, Coord /*xy*/, Color /*color*/)
{
    // Replace this with your implementation
    return false;
}

std::string Datastructures::get_name(BeaconID /*id*/)
{
    // Replace this with your implementation
    return NO_NAME;
}

Coord Datastructures::get_coordinates(BeaconID /*id*/)
{
    // Replace this with your implementation
    return NO_COORD;
}

Color Datastructures::get_color(BeaconID /*id*/)
{
    // Replace this with your implementation
    return NO_COLOR;
}


std::vector<BeaconID> Datastructures::beacons_alphabetically()
{
    // Replace this with your implementation
    return {};
}

std::vector<BeaconID> Datastructures::beacons_brightness_increasing()
{
    // Replace this with your implementation
    return {};
}

BeaconID Datastructures::min_brightness()
{
    // Replace this with your implementation
    return NO_ID;
}

BeaconID Datastructures::max_brightness()
{
    // Replace this with your implementation
    return NO_ID;
}

std::vector<BeaconID> Datastructures::find_beacons(std::string const& /*name*/)
{
    // Replace this with your implementation
    return {};
}

bool Datastructures::change_beacon_name(BeaconID /*id*/, const std::string& /*newname*/)
{
    // Replace this with your implementation
    return false;
}

bool Datastructures::change_beacon_color(BeaconID /*id*/, Color /*newcolor*/)
{
    // Replace this with your implementation
    return false;
}

bool Datastructures::add_lightbeam(BeaconID /*sourceid*/, BeaconID /*targetid*/)
{
    // Replace this with your implementation
    return false;
}

std::vector<BeaconID> Datastructures::get_lightsources(BeaconID /*id*/)
{
    // Replace this with your implementation
    return {};
}

std::vector<BeaconID> Datastructures::path_outbeam(BeaconID /*id*/)
{
    // Replace this with your implementation
    return {NO_ID};
}

bool Datastructures::remove_beacon(BeaconID /*id*/)
{
    // Replace this with your implementation
    return false;
}

std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID /*id*/)
{
    // Replace this with your implementation
    return {NO_ID};
}

Color Datastructures::total_color(BeaconID /*id*/)
{
    // Replace this with your implementation
    return NO_COLOR;
}

std::vector<Coord> Datastructures::all_xpoints()
{
    // Replace this with your implementation
    return {};
}

bool Datastructures::add_fibre(Coord /*xpoint1*/, Coord /*xpoint2*/, Cost /*cost*/)
{
    // Replace this with your implementation
    return false;
}

std::vector<std::pair<Coord, Cost> > Datastructures::get_fibres_from(Coord /*xpoint*/)
{
    // Replace this with your implementation
    return {};
}

std::vector<std::pair<Coord, Coord> > Datastructures::all_fibres()
{
    // Replace this with your implementation
    return {};
}

bool Datastructures::remove_fibre(Coord /*xpoint1*/, Coord /*xpoint2*/)
{
    // Replace this with your implementation
    return false;
}

void Datastructures::clear_fibres()
{
    // Replace this with your implementation
}

std::vector<std::pair<Coord, Cost> > Datastructures::route_any(Coord /*fromxpoint*/, Coord /*toxpoint*/)
{
    // Replace this with your implementation
    return {};
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_least_xpoints(Coord /*fromxpoint*/, Coord /*toxpoint*/)
{
    // Replace this with your implementation
    return {};
}

std::vector<std::pair<Coord, Cost>> Datastructures::route_fastest(Coord /*fromxpoint*/, Coord /*toxpoint*/)
{
    // Replace this with your implementation
    return {};
}

std::vector<Coord> Datastructures::route_fibre_cycle(Coord /*startxpoint*/)
{
    // Replace this with your implementation
    return {};
}

Cost Datastructures::trim_fibre_network()
{
    // Replace this with your implementation
    return NO_COST;
}
