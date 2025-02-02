#pragma once

#include <raylib.h>
#include <string>
#include <vector>

struct Achievement{
    std::string secret_name;
    std::vector<Vector2> reference_points;
    std::string reference_image_name;
    std::string solution_image_name;
    bool final = false;
};