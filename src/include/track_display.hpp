#ifndef TRACK_DISPLAY_HPP
#define TRACK_DISPLAY_HPP

#include "polygon_perimeter.hpp"
#include "ppm_image.hpp"

#include <list>

struct TrackDisplay {
    constexpr static RGB background_clr = {32, 32, 32};
    constexpr static RGB source_clr     = {0, 255, 0};
    constexpr static RGB estimated_clr  = {177, 3, 252};
    constexpr static RGB collision_clr  = {255, 0, 0};
    constexpr static RGB perimeter_clr  = {0, 127, 255};

    void init(int in_width, int in_height, const std::string& in_path_base);
    void draw_perimeter(std::shared_ptr<PolygonPerimeter> perimeter);
    void display_marker(track2d::Vector2D plot_space_coordinates, const RGB& clr);
    void refresh(const track2d::TrackDisplayMessage& msg);
    void display_frame();

    RGBImage img;
    ssize_t frame_counter = 0;
    int width;
    int height;
    std::string path_base;
    std::list<track2d::Vector2D> estimated_plots;
    std::optional<track2d::Vector2D> collision;
    track2d::Vector2D display_coordinate_offset;
}; // TrackDisplay

#endif // TRACK_DISPLAY_HPP
