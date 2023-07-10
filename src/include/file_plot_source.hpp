#ifndef FILE_PLOT_SOURCE_HPP
#define FILE_PLOT_SOURCE_HPP

#include "../../track2d-lib/include/track2d.hpp"

#include <list>
#include <optional>
#include <string>

class FilePlotSource : public track2d::IPlotSource {
public:
    FilePlotSource(const std::string path);
    ~FilePlotSource();
    std::optional<track2d::Plot> get() final override;
    bool advance() final override;
    
private:
    std::list<track2d::Plot> m_plot_list;
}; // FilePlotSource

#endif // FILE_PLOT_SOURCE_HPP
