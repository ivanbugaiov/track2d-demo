#include "../track2d-lib/include/track2d.hpp"

#include "include/file_plot_source.hpp"
#include "include/polygon_perimeter.hpp"
#include "include/track2d_demo_utils.hpp"

#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Hello Track2d!" << std::endl;    

    if (argc != 3) {
        std::cerr << "error: invalid number of arguments" << std::endl;
        help();
        return -1;
    }            
    
    auto plot_file_path = std::string(argv[1]);
    auto perimeter_file_path = std::string(argv[2]);   
    
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

    auto linear_estimator = 
        std::make_shared<track2d::TrackEstimator>(file_plot_source, 
                                                  track2d::TrackEstimator::Model::linear);
    
    // consume all plot data at once
    
    // after much consideration a decicion to avoid implicit advance was made
    // hence neither estimator nor plot source are slaved to one another
    // and both are advanced explicitly for maximum flexibility of use cases
    while (linear_estimator->advance()) {
        file_plot_source->advance();
    }
    
    auto perimeter = load_perimeter_from_file(perimeter_file_path);
    if (!perimeter) {
        std::cerr << "error: could not load perimeter from file" << std::endl;
        return -1;
    }
    
    std::cout << "perimeter:" << std::endl;
    perimeter->display();
    std::cout << std::endl;

    double look_ahead_interval = 10.0;

    std::optional<track2d::ITrackEstimator::Result> result = 
        linear_estimator->get_expected_crossing(perimeter, look_ahead_interval);
    
    if (result) {
        std::cout << "track is expected to cross perimeter" << std::endl;
        std::cout << "  estimated time: " << result->plot.time << std::endl;
        std::cout << "  estimated coordinates: " << result->plot.loc.x << ", " << result->plot.loc.y << std::endl;
        std::cout << "  estimated speed: " << get_vector_length(result->speed)  << std::endl;
        std::cout << "  estimated orientation: " << get_vector_angle(result->speed) << std::endl;
    } else {
        std::cout << "track does not cross the perimeter" << std::endl;
    }
    
    return 0;
} // main
