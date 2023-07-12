#include "include/ppm_image.hpp"

RGBImage::RGBImage() {
    resize(0, 0);
}

RGBImage::RGBImage(int rows, int cols, RGB clr) {
    resize(rows, cols, clr);
}

RGBImage::RGBImage(int rows, int cols, std::vector<std::vector<RGB>> data)
    : m_data(std::move(data))
    , m_rows(rows)
    , m_cols(cols)
{}

void RGBImage::resize(int rows, int cols, RGB clr) {
    m_rows = rows;
    m_cols = cols;
    m_data.resize(rows, std::vector<RGB>(cols, clr));
}

const RGB& RGBImage::at(int y, int x) const {
    return m_data.at(y).at(x);
}

RGB& RGBImage::at(int y, int x) {
    return m_data.at(y).at(x);
}

void RGBImage::set(int y, int x, RGB clr) {
    if (y >= 0 && x >= 0 && y < m_rows && x < m_cols) {
        m_data.at(y).at(x) = clr;
    }
}

const RGBImage::Row& RGBImage::row(int y) const {
    return m_data.at(y);
}

RGBImage::Row& RGBImage::row(int y) {
    return m_data.at(y);
}

const int RGBImage::rows() const {
    return m_rows;
}

const int RGBImage::cols() const {
    return m_cols;
}

std::shared_ptr<RGBImage> PPMReader::read(const std::string& path) {
    std::ifstream ppm_file(path, std::ifstream::binary);
    // Examine if the file could be opened successfully
    if (!ppm_file.is_open()) {
        std::cout << "Failed to open " << path << std::endl;
        return nullptr;
    }

    std::string ppm_magic;
    ppm_file >> ppm_magic;

    ppm_file.seekg(1, ppm_file.cur);

    char c;
    ppm_file.get(c);
    if (c == '#') {
        while (c != '\n') {
            ppm_file.get(c);
        }
    } else {
        ppm_file.seekg(-1, ppm_file.cur);
    }

    int rows, cols, max;
    ppm_file >> cols >> rows >> max;

    RGBImage::Data data(rows, RGBImage::Row(cols));

    if (ppm_magic == "P6") {
        // Move curser once to skip '\n'
        ppm_file.seekg(1, ppm_file.cur);
        for (auto y = 0; y < rows; ++y) {
            ppm_file.read(reinterpret_cast<char *>(data.at(y).data()), cols * RGB_COMPONENT_COUNT);
        }
    } else {
        std::cerr << "could not recognize format" << std::endl;
        return nullptr;
    }

    return std::make_shared<RGBImage>(rows, cols, data);
} // read

void PPMWriter::write(const std::string& path, const RGBImage& img) {
    std::string ppm_magic = PPM_HEADER_MAGIC;
    int max_value = 255;

    std::ofstream ppm_file(path, std::ofstream::binary);
    if (ppm_file.fail()) {
        std::cerr << "error: could not open file for writing" << std::endl;
        return;
    }
    ppm_file << ppm_magic << "\n" << img.cols() << " " << img.rows() << "\n" << max_value << "\n";

    for (auto y = 0; y < img.rows(); ++y) {
        ppm_file.write(reinterpret_cast<const char *>(img.row(y).data()), img.cols() * RGB_COMPONENT_COUNT);
    }

    return;
} // write
