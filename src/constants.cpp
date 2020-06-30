#include "../include/constants.h"

extern unordered_map<string, FireDirection> DIRECTIONS = {
    {"t",  FireDirection::TOP()},
    {"r",  FireDirection::RIGHT()},
    {"b",  FireDirection::BOTTOM()},
    {"l",  FireDirection::LEFT()},
    {"tr", FireDirection::TOP_RIGHT()},
    {"br", FireDirection::BOTTOM_RIGHT()},
    {"bl", FireDirection::BOTTOM_LEFT()},
    {"tl", FireDirection::TOP_LEFT()},
};


