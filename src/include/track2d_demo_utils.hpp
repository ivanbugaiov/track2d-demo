#ifndef TRACK2D_DEMO_UTILS_HPP
#define TRACK2D_DEMO_UTILS_HPP

#include "../../track2d-lib/include/track2d.hpp"
#include "polygon_perimeter.hpp"

#include <string>

bool check_double_equal(double first, double second);

void help();

std::shared_ptr<PolygonPerimeter> load_perimeter_from_file(const std::string& path);

class Statistics {
public:
    Statistics();
    ~Statistics();

    void reset();
    void put(double val);

    double get_min() const;
    double get_max() const;
    double get_avg() const;
    double get_var() const;
    double get_std() const;
    unsigned int get_count() const;

    void print() const;

private:
    double sum;
    double squares_sum;
    double min;
    double max;
    unsigned int count;
}; // Statistics

#endif // TRACK2D_DEMO_UTILS_HPP
