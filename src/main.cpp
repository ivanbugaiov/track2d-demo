#include "../track2d-lib/include/track2d.hpp"

#include "include/file_plot_source.hpp"
#include "include/polygon_perimeter.hpp"
#include "include/ppm_image.hpp"
#include "include/track2d_demo_utils.hpp"
#include "include/track_display.hpp"

#include <iostream>
#include <string>

static TrackDisplay track_display;

static void track_display_callback(const track2d::TrackDisplayMessage& msg) {
    track_display.refresh(msg);
} // track_display_callback

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "error: invalid number of arguments" << std::endl;
        help();
        return -1;
    }            
    
    auto perimeter_file_path = std::string(argv[2]);   
    auto perimeter = load_perimeter_from_file(perimeter_file_path);
    if (!perimeter) {
        std::cerr << "error: could not load perimeter from file" << std::endl;
        return -1;
    }
    
    track_display.init(1024, 1024, "frame_");
    track_display.draw_perimeter(perimeter);

    std::cout << "perimeter:" << std::endl;
    perimeter->display();
    std::cout << std::endl;
    
    auto plot_file_path = std::string(argv[1]);
    std::shared_ptr<FilePlotSource> file_plot_source;
    try {
        file_plot_source = std::make_shared<FilePlotSource>(plot_file_path);
    } catch(std::exception const& e) {
        std::cout << "error: " << e.what() << std::endl;
        return -1;
    } 

    std::cout << "plot data:" << std::endl;
    file_plot_source->display();
    std::cout << std::endl;

    auto estimator = 
        std::make_shared<track2d::TrackEstimator>(file_plot_source, 
                                                  track2d::TrackEstimator::Model::global_average,
                                                  track_display_callback);
    while (estimator->advance()) {
        std::optional<track2d::ITrackEstimator::Result> result = estimator->get_expected_crossing(perimeter);
        if (result) {
            std::cout << "track is expected to cross perimeter" << std::endl;
            std::cout << "  estimated time: " << result->plot.time << std::endl;
            std::cout << "  estimated coordinates: " << result->plot.loc.x << ", " << result->plot.loc.y << std::endl;
            std::cout << "  estimated speed: " << result->speed  << std::endl;
            std::cout << "  estimated orientation: " << result->angle << std::endl;
        } else {
            std::cout << "track does not cross the perimeter" << std::endl;
        }
                                         
        file_plot_source->advance();
    }
    
    return 0;
} // main
