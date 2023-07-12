#ifndef PPM_IMAGE_HPP
#define PPM_IMAGE_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#define RGB_COMPONENT_COUNT 3
#define PPM_HEADER_MAGIC "P6"

struct RGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
}; // RGB

class PPMReader;
class PPMWriter;

class RGBImage {
public:
    using Row = std::vector<RGB>;
    using Data = std::vector<Row>;
public:
    RGBImage();
    RGBImage(int rows, int cols, RGB clr = {0, 0, 0});
    RGBImage(int rows, int cols, std::vector<std::vector<RGB>> data);

    void resize(int rows, int cols, RGB clr = {0, 0, 0});

    const RGB& at(int y, int x) const;
    RGB& at(int y, int x);

    void set(int y, int x, RGB clr);

    const Row& row(int y) const;
    Row& row(int y);

    const int rows() const;
    const int cols() const;

private:
    Data m_data;
    int m_rows = 0;
    int m_cols = 0;
}; // RGBImage

class PPMReader {
public:
    static std::shared_ptr<RGBImage> read(const std::string& path);
}; // PPMReader

class PPMWriter {
public:
    static void write(const std::string& path, const RGBImage& img);
}; // PPMWriter

#endif // PPM_IMAGE_HPP
