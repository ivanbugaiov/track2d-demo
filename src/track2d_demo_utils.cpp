#include "include/file_plot_source.hpp"
#include "include/polygon_perimeter.hpp"
#include "include/track2d_demo_utils.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

bool check_double_equal(double first, double second) {
    constexpr static double eps = 1.0 / 1000000.0;
    return std::abs(first - second) <= std::abs(eps * std::max(first, second));
}

void help() {
    std::cout << "Usage: track2d-demo TRACK RECT" << std::endl;
} // help

std::shared_ptr<PolygonPerimeter> load_perimeter_from_file(const std::string& path) {
    std::fstream perimeter_file(path, std::ios_base::in);
    if (perimeter_file) {
        std::vector<track2d::Vector2D> points;
        std::string line;
        
        while (std::getline(perimeter_file, line)) {
            track2d::Vector2D pt;
            sscanf(line.c_str(),"%lf,%lf", &(pt.x), &(pt.y));
            points.push_back(pt);
        }
     
        return std::make_shared<PolygonPerimeter>(points);
    } else {
        std::cerr << "error: could not open file '" << path << "' for reading" << std::endl;
        return nullptr;    
    }
} // load_perimeter_from_file

