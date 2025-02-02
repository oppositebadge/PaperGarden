#pragma once

#include <raylib.h>
#include <string>
#include <vector>

struct Achievement{
    std::vector<Vector2> reference_points;
    std::string reference_image_name;
    bool final = false;
};