#pragma once

#include <raylib.h>
#include <string>
#include <vector>

struct Unlock{
    std::vector<Vector2> reference_points;
    std::string reference_image_name;

    bool unlocked = false;
};