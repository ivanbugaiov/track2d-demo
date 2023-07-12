#include "include/track_display.hpp"

void TrackDisplay::init(int in_width, int in_height, const std::string& in_path_base) {
} // init

void TrackDisplay::draw_perimeter(std::shared_ptr<PolygonPerimeter> perimeter) {
} // draw_perimeter

void TrackDisplay::display_marker(const track2d::Vector2D& plot_space_coordinates, const RGB& clr) {
}; // display_marker

void TrackDisplay::refresh(const track2d::TrackDisplayMessage& msg) {
} // refresh

void TrackDisplay::display_frame() {
} // display_frame
