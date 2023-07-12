#include "include/polygon_perimeter.hpp"
#include "include/track2d_demo_utils.hpp"

#include <iostream>
#include <cmath>
#include <optional>

static std::optional<track2d::Vector2D> get_segment_intersection(
        const track2d::Vector2D& s1pt1,
        const track2d::Vector2D& s1pt2,
        const track2d::Vector2D& s2pt1,
        const track2d::Vector2D& s2pt2) {
    double a1 = (s1pt2.x - s1pt1.x);
    double b1 = (s2pt1.x - s2pt2.x);

    double a2 = (s1pt2.y - s1pt1.y);
    double b2 = (s2pt1.y - s2pt2.y);

    double divisor = (a1 * b1) - (a2 * b1);
    if (check_double_equal(divisor, 0.0)) {
        // lines are parallel so no crossing
        return std::nullopt;
    }

    double c1 = (s2pt1.x - s1pt1.x);
    double c2 = (s2pt1.y - s1pt1.y);

    double param_s1 = ((b2 * c1) - (b1 * c2));
    double param_s2 = ((a1 * c2) - (a2 * c1));

    // division is delayed to save ticks in case there is no crossing
    if (param_s1 >= 0.0 && param_s2 >= 0 && param_s1 <= divisor && param_s2 <= divisor) {
        param_s1 /= divisor;

        track2d::Vector2D res;

        res.x = s1pt1.x + (s1pt2.x - s1pt1.x) * param_s1;
        res.y = s1pt1.y + (s1pt2.y - s1pt1.y) * param_s1;

        return res;
    }

    return std::nullopt;
} // check_segment_intersection

PolygonPerimeter::PolygonPerimeter(std::vector<track2d::Vector2D> points)
    : m_points(std::move(points))
{
    m_intersection_points.reserve(m_points.size());
    for (const auto& pt : m_points) {
        if (pt.x > m_max_x) { m_max_x = pt.x; }
        if (pt.y > m_max_y) { m_max_y = pt.y; }
        if (pt.x < m_min_x) { m_min_x = pt.x; }
        if (pt.y < m_min_y) { m_min_y = pt.y; }
    }
} // PolygonPerimeter

std::optional<track2d::Vector2D> PolygonPerimeter::get_crossing_point(const track2d::Vector2D& approach_point,
                                                                      const track2d::Vector2D& unknown_point) {
    // first, quick bounding box check
    if (unknown_point.x < m_min_x
            || unknown_point.x > m_max_x
            || unknown_point.y < m_min_y
            || unknown_point.y > m_max_y) {
        return std::nullopt;
    }

    // the point is inside the bounding box, a more accurate check has to be made
    track2d::Vector2D crossing_segment_pt1 = approach_point;
    track2d::Vector2D crossing_segment_pt2 = unknown_point;
    track2d::Vector2D perimeter_segment_pt1 = m_points.back();

    m_intersection_points.clear();
    for (auto i = 0; i < m_points.size(); ++i) {
        track2d::Vector2D perimeter_segment_pt2 = m_points.at(i);
        auto res = get_segment_intersection(perimeter_segment_pt1,
                                            perimeter_segment_pt2,
                                            crossing_segment_pt1,
                                            crossing_segment_pt2);
        if (res.has_value()) {
            m_intersection_points.push_back(res.value());
        }

        perimeter_segment_pt1 = m_points.at(i);
    }

    if (m_intersection_points.empty()) {
        return std::nullopt;
    }

    auto distance_between_points = [](const track2d::Vector2D& pt1, const track2d::Vector2D& pt2) {
        double aux1 = pt1.x - pt2.x;
        double aux2 = pt1.y - pt2.y;
        return sqrt(aux1 * aux1 + aux2 * aux2);
    };

    track2d::Vector2D nearest_intersection_point;
    double min_intersection_distance = std::numeric_limits<double>::max();
    for (const auto& pt: m_intersection_points) {
        double intersection_distance = distance_between_points(approach_point, pt);
        if (intersection_distance < min_intersection_distance) {
            min_intersection_distance = intersection_distance;
            nearest_intersection_point = pt;
        }
    }

    return nearest_intersection_point;
} // get_crossing_point

bool PolygonPerimeter::is_point_inside(const track2d::Vector2D& unknown_point) {
    track2d::Vector2D point_outside_bb(m_min_x - 1, m_min_y - 1);
    if (!get_crossing_point(point_outside_bb, unknown_point).has_value()) {
        return false;
    }

    return m_intersection_points.size() % 2 == 1;
} // is_point_inside

void PolygonPerimeter::display() const {
    for (const auto& pt : m_points) {
        std::cout << pt.x << "," << pt.y << std::endl;
    }
    
    std::cout << std::endl;
} // display

