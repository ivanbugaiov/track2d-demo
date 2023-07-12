#include "../track2d-lib/include/track2d.hpp"

#include "include/file_plot_source.hpp"
#include "include/polygon_perimeter.hpp"
#include "include/ppm_image.hpp"
#include "include/track_display.hpp"
#include "include/track2d_demo_utils.hpp"

#include <iostream>
#include <string>

void TrackDisplay::init(int in_width, int in_height, const std::string& in_path_base) {
    width = in_width;
    height = in_height;
    path_base = in_path_base;
    img.resize(height, width, background_clr);
    display_coordinate_offset = {width / 2, height / 2};
} // init

void TrackDisplay::draw_perimeter(std::shared_ptr<PolygonPerimeter> perimeter) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (perimeter->is_point_inside({x, y})) {
                img.set(display_coordinate_offset.y - y, x + display_coordinate_offset.x, perimeter_clr);
            }
        }
    }
} // draw_perimeter

void TrackDisplay::display_marker(track2d::Vector2D plot_space_coordinates, const RGB& clr) {
    int x = plot_space_coordinates.x + display_coordinate_offset.x;
    int y = display_coordinate_offset.y - plot_space_coordinates.y;

    img.set(y - 1, x - 1, clr);
    img.set(y - 1, x + 0, clr);
    img.set(y - 1, x + 1, clr);
    img.set(y + 0, x - 1, clr);
    img.set(y + 0, x + 0, clr);
    img.set(y + 0, x + 1, clr);
    img.set(y + 1, x - 1, clr);
    img.set(y + 1, x + 0, clr);
    img.set(y + 1, x + 1, clr);
    img.set(y - 2, x - 2, clr);
    img.set(y - 2, x - 1, clr);
    img.set(y - 2, x + 0, clr);
    img.set(y - 2, x + 1, clr);
    img.set(y - 2, x + 2, clr);
    img.set(y - 1, x - 2, clr);
    img.set(y - 1, x + 2, clr);
    img.set(y + 0, x - 2, clr);
    img.set(y + 0, x + 2, clr);
    img.set(y + 1, x - 2, clr);
    img.set(y + 1, x + 2, clr);
    img.set(y + 2, x - 2, clr);
    img.set(y + 2, x - 1, clr);
    img.set(y + 2, x + 0, clr);
    img.set(y + 2, x + 1, clr);
    img.set(y + 2, x + 2, clr);
}; // display_marker

void TrackDisplay::refresh(const track2d::TrackDisplayMessage& msg) {
    switch (msg.plot_type) {
        case track2d::TrackDisplayMessage::PlotType::source:
            if (!estimated_plots.empty() || collision.has_value()) {
                display_frame();

                for (const auto& pt: estimated_plots) {
                    display_marker(pt, background_clr);
                }

                estimated_plots.clear();
                if (collision.has_value()) {
                    display_marker(collision.value(), background_clr);
                    collision = std::nullopt;
                }
            }

            std::cout << "display source plot at " << msg.plot.loc << std::endl;
            display_marker(msg.plot.loc, source_clr);
            display_frame();
            break;
        case track2d::TrackDisplayMessage::PlotType::estimate:
            std::cout << "display estimated plot at " << msg.plot.loc << std::endl;
            estimated_plots.push_back(msg.plot.loc);
            break;
        case track2d::TrackDisplayMessage::PlotType::collision:
            std::cout << "display collision at " << msg.plot.loc << std::endl;
            collision = msg.plot.loc;
            break;

    }
} // refresh

void TrackDisplay::display_frame() {
    if (!estimated_plots.empty()) {
        for (const auto& pt: estimated_plots) {
            display_marker(pt, estimated_clr);
        }
    }

    if (collision.has_value()) {
        display_marker(collision.value(), collision_clr);
    }

    char buffer[256];
    sprintf(buffer, "%08lu\0", frame_counter);
    std::string frame_path = path_base + std::string(buffer) + ".ppm";
    PPMWriter::write(frame_path, img);

    frame_counter += 1;
} // display_frame
