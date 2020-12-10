/*
AR Tag Identifier by Stanley Su
Requires OpenCV and C++11.
Compilation: g++ identifier.cpp -o identifier -std=c++11 `pkg-config --cflags --libs opencv`
Usage: ./identifier image_path [tag_size]
*/
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

#define CELL_SIZE 50 // length in pixels of each AR tag square

int main(int argc, char **argv) {
    int TAG_SIZE = 9; // default of 9
    
    // parse command line arguments
    string usage = "Usage: ./identifier image_path [tag_size]";
    if (argc <= 1 || argc > 3) {
        cout << usage << endl;
        return 1;
    }
    // if tag_size was specified
    if (argc == 3) {
        TAG_SIZE = stoi(argv[2]);
    }
    auto image_path = argv[1];
    
    // read in the image as grayscale
    Mat img = imread(image_path, IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "Could not read the image: " << image_path << endl;
        return 1;
    }

    // resize the image so each grid cell is of integer length
    // that is, each cell will be 50 by 50 pixels
    resize(img, img, Size(TAG_SIZE * CELL_SIZE, TAG_SIZE * CELL_SIZE));

    // transform image to grayscale if not converted whilst reading it in
    if (img.channels() == 3) {
        cvtColor(img, img, CV_BGR2GRAY);
    }

    imshow("Initial AR tag", img);
    waitKey(0); // Wait for a keystroke in the window

    // otsu threshold the image
    threshold(img, img, 0, 255, CV_THRESH_OTSU);

    // erode squares or points smaller than 30% of a grid cell
    // number chosen empirically and intuitively
    int erode_length = 0.3 * CELL_SIZE;
    // kernel for removing small points that are most likely noise
    Mat element = getStructuringElement(MORPH_RECT, Size(erode_length, erode_length));
    // remove small objects (it is assumed that the objects are bright on a dark foreground)
    morphologyEx(img, img, MORPH_OPEN, element);

    // small holes would be around a 10th of a cell's size (chosen empirically)
    erode_length = 0.1 * CELL_SIZE;
    element = getStructuringElement(MORPH_RECT, Size(erode_length, erode_length));
    // remove small holes (small dark regions)
    morphologyEx(img, img, MORPH_CLOSE, element);

    // represent each square's colour (0 as black, 1 as white) in matrix
    vector<vector<int>> matrix(TAG_SIZE, vector<int>(TAG_SIZE));

    const auto rows = img.rows; // total pixels vertically
    const auto cols = img.cols; // total pixels horizontally

    // percent of each cell's width in-between
    // the edge and the content to ignore
    const auto padding = 0.05; // 5%, means total of 10% of the cell lengthwise will be ignored

    const int content_len = (1 - (2 * padding)) * CELL_SIZE;

    // loop through each cell in the image
    for (int y = 0; y < TAG_SIZE; ++y) {
        int start_y = (y * CELL_SIZE) + ((padding) * CELL_SIZE);
        for (int x = 0; x < TAG_SIZE; ++x) {
            int start_x = (x * CELL_SIZE) + ((padding) * CELL_SIZE);
            // calculate average pixel intensity in the cell
            Rect roi(start_x, start_y, content_len, content_len);
            Scalar mean, dev;
            meanStdDev(img(roi), mean, dev);

            // determine if black or white based on midpoint threshold
            int colour = (mean[0] < 128) ? 0 : 1;
            matrix[y][x] = colour;
        }
    }

    // output the matrix
    for ( const auto &row : matrix ) {
        for ( const auto &s : row ) cout << s << ' ';
        cout << endl;
    }

    imshow("Cleaned AR tag", img);
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}