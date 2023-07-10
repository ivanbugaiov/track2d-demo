#include "include/file_plot_source.hpp"
#include "include/polygon_perimeter.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

double get_vector_length(const track2d::vector2d_t& vec) {
    return 0.0;
} // get_vector_length

double get_vector_angle(const track2d::vector2d_t& vec) {
    return 0.0;
} // get_vector_angle

void help() {
    std::cout << "Usage: track2d-demo TRACK RECT" << std::endl;
} // help

std::shared_ptr<PolygonPerimeter> load_perimeter_from_file(const std::string& path) {
    std::fstream perimeter_file(path, std::ios_base::in);
    if (perimeter_file) {
        std::vector<track2d::point2d_t> points;
        std::string line;
        
        while (std::getline(perimeter_file, line)) {
            track2d::point2d_t pt;
            sscanf(line.c_str(),"%lf,%lf", &(pt.x), &(pt.y));
            points.push_back(pt);
        }
     
        return std::make_shared<PolygonPerimeter>(points);
    } else {
        std::cerr << "error: could not open file '" << path << "' for reading" << std::endl;
        return nullptr;    
    }
} // load_perimeter_from_file

