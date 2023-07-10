#include "include/file_plot_source.hpp"
    
#include <iostream>
#include <fstream>
#include <string>

FilePlotSource::FilePlotSource(const std::string path) {
    std::fstream plot_file(path, std::ios_base::in);
    if (plot_file) {
        std::string line;

        while (std::getline(plot_file, line)) {
            track2d::Plot plot;
            sscanf(line.c_str(),"%lf,%lf,%lf", &(plot.time), &(plot.loc.x), &(plot.loc.y));
            m_plot_list.push_back(plot);
        }
    } else {
        std::cerr << "error: could not open file '" << path << "' for reading" << std::endl;
        throw std::runtime_error("could not load plot from file");
    }
}

FilePlotSource::~FilePlotSource() {

}
    
std::optional<track2d::Plot> FilePlotSource::get() {
    if (m_plot_list.empty()) {
        return std::nullopt;
    }
    
    return m_plot_list.front();
} // get

bool FilePlotSource::advance() {
    if (m_plot_list.empty()) {
        return false;
    }
    
    m_plot_list.pop_front();
    return m_plot_list.empty();
} // advance

void FilePlotSource::display() const {
    for (const auto& plot : m_plot_list) {
        std::cout << plot.time << " " << plot.loc.x << " " << plot.loc.y << std::endl;
    }
} // display
