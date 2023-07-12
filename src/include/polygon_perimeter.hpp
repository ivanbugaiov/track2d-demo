#ifndef POLYGON_PERIMETER_HPP
#define POLYGON_PERIMETER_HPP

#include "../../track2d-lib/include/track2d.hpp"

#include <limits>
#include <vector>

class PolygonPerimeter : public track2d::IPerimeter {
public:
    PolygonPerimeter(std::vector<track2d::Vector2D> points);    
    std::optional<track2d::Vector2D> get_crossing_point(const track2d::Vector2D& approach_point,
                                                         const track2d::Vector2D& unknown_point) final override;

    bool is_point_inside(const track2d::Vector2D& unknown_point);
    void display() const;

private:
    std::vector<track2d::Vector2D> m_intersection_points;
    std::vector<track2d::Vector2D> m_points;
    double m_min_x = std::numeric_limits<double>::max();
    double m_min_y = std::numeric_limits<double>::max();
    double m_max_x = std::numeric_limits<double>::min();
    double m_max_y = std::numeric_limits<double>::min();
}; // PolygonPerimeter

#endif // POLYGON_PERIMETER_HPP
