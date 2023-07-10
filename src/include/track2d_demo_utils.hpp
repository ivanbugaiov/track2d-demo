#ifndef TRACK2D_DEMO_UTILS_HPP
#define TRACK2D_DEMO_UTILS_HPP

#include "track2d-lib/include/track2d.hpp"

#include <string>

double get_vector_length(const track2d::vector2d_t& vec);

double get_vector_angle(const track2d::vector2d_t& vec);

void help();

std::shared_ptr<PolygonPerimeter> load_perimeter_from_file(const std::string& path);

#endif // TRACK2D_DEMO_UTILS_HPP
