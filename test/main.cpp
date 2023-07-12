#include "../src/include/track2d_demo_utils.hpp"
#include "../src/include/ppm_image.hpp"
#include "../src/include/polygon_perimeter.hpp"

#include <iostream>

void test_polygon_perimeter() {
    std::cout << "********************************" << std::endl;
    std::cout << "**** test_polygon_perimeter ****" << std::endl;
    std::cout << "********************************" << std::endl << std::endl;

    { // square perimeter, target point inside perimeter, expected crossing
        std::cout << "TEST #1" << std::endl;
        std::vector<track2d::Vector2D> points {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
        track2d::Vector2D approach_point {-2, 0};
        track2d::Vector2D target_point {0, 0};
        track2d::Vector2D expected_crossing_point {-1, 0};

        PolygonPerimeter perimeter(points);
        std::cout << "perimeter:" << std::endl;
        perimeter.display();

        std::cout << "approach point: " << approach_point.x << ", " << approach_point.y << std::endl;
        std::cout << "target point: " << target_point.x << ", " << target_point.y << std::endl;
        std::cout << "expected crossing: " << expected_crossing_point.x << ", " << expected_crossing_point.y << std::endl;

        auto res = perimeter.get_crossing_point(approach_point, target_point);
        if (!res.has_value()) {
            std::cout << "FAIL" << std::endl;
        } else {
            track2d::Vector2D crossing_point = res.value();
            std::cout << "crossing detected at " << crossing_point.x << ", " << crossing_point.y << std::endl;

            if (check_double_equal(crossing_point.x, expected_crossing_point.x)
                    && check_double_equal(crossing_point.y, expected_crossing_point.y)) {
                std::cout << "PASS" << std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        }

        std::cout << std::endl;
    }

    { // square perimeter, target point outside perimeter, crossing not expected
        std::cout << "TEST #2" << std::endl;
        std::vector<track2d::Vector2D> points {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
        track2d::Vector2D approach_point {-2, 0};
        track2d::Vector2D target_point {-4, 0};

        PolygonPerimeter perimeter(points);
        std::cout << "perimeter:" << std::endl;
        perimeter.display();

        std::cout << "approach point: " << approach_point.x << ", " << approach_point.y << std::endl;
        std::cout << "target point: " << target_point.x << ", " << target_point.y << std::endl;
        std::cout << "crossing not expected" << std::endl;

        auto res = perimeter.get_crossing_point(approach_point, target_point);
        if (!res.has_value()) {
            std::cout << "PASS" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }

        std::cout << std::endl;
    }

    // currently this test fails
    // this shows the limitation of fast bounding box pre-check: overshots are not detected as crossings
    // even though there would be multiple crossings, nothing is detected
    // still the performance boost is worth it

    { // square perimeter, target point outside perimeter, expected crossing
        std::cout << "TEST #3" << std::endl;
        std::vector<track2d::Vector2D> points {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
        track2d::Vector2D approach_point {-2, 0};
        track2d::Vector2D target_point {2, 0};
        track2d::Vector2D expected_crossing_point {-1, 0};

        PolygonPerimeter perimeter(points);
        std::cout << "perimeter:" << std::endl;
        perimeter.display();

        std::cout << "approach point: " << approach_point.x << ", " << approach_point.y << std::endl;
        std::cout << "target point: " << target_point.x << ", " << target_point.y << std::endl;
        std::cout << "expected crossing: " << expected_crossing_point.x << ", " << expected_crossing_point.y << std::endl;

        auto res = perimeter.get_crossing_point(approach_point, target_point);
        if (!res.has_value()) {
            std::cout << "FAIL" << std::endl;
        } else {
            track2d::Vector2D crossing_point = res.value();
            std::cout << "crossing detected at " << crossing_point.x << ", " << crossing_point.y << std::endl;

            if (check_double_equal(crossing_point.x, expected_crossing_point.x)
                    && check_double_equal(crossing_point.y, expected_crossing_point.y)) {
                std::cout << "PASS" << std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        }

        std::cout << std::endl;
    }
}

void test_ppm_image() {
    std::cout << "********************************" << std::endl;
    std::cout << "****     test_ppm_image     ****" << std::endl;
    std::cout << "********************************" << std::endl << std::endl;

    { // smoke
        std::cout << "TEST #1" << std::endl;

        RGBImage img(32, 32);
        std::cout << "write image size: " << img.cols() << "x" << img.rows() << std::endl;
        PPMWriter::write("img.ppm", img);
        auto read_img = PPMReader::read("img.ppm");
        std::cout << "read image size: " << read_img->cols() << "x" << read_img->rows() << std::endl;
    }
}

int main(int argc, char** argv) {
    test_polygon_perimeter();
    test_ppm_image();
    return 0;
}
