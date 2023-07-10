#include "include/polygon_perimeter.hpp"

#include <iostream>

PolygonPerimeter::PolygonPerimeter(std::vector<track2d::point2d_t> points)
    : m_points(std::move(points))
{} // PolygonPerimeter

bool PolygonPerimeter::is_point_inside(const track2d::point2d_t& pt) {
    return false;
} // is_point_inside

void PolygonPerimeter::display() const {
    for (const auto& pt : m_points) {
        std::cout << pt.x << "," << pt.y << std::endl;
    }
    
    std::cout << std::endl;
} // display

