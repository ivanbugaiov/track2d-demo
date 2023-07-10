#ifndef POLYGON_PERIMETER_HPP
#define POLYGON_PERIMETER_HPP

#include "track2d-lib/include/track2d.hpp"

#include <vector>

class PolygonPerimeter : public track2d::IPerimeter {
public:
    PolygonPerimeter(std::vector<track2d::point2d_t> points);    
    bool is_point_inside(const track2d::point2d_t& pt) final override;
    void display() const;
    
private:
    std::vector<track2d::point2d_t> m_points;
}; // PolygonPerimeter

#endif // POLYGON_PERIMETER_HPP
