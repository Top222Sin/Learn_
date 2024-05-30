#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <string>
#include <utility>
#include <cstdint>
#include <cstdint>  // for uint16_t

using namespace std;

int height = 1200;
int width = 1600;
int channels = 36;

// Function to calculate slope
float calculate_slope(float x1, float y1, float x2, float y2) {
    return (y2 - y1) / (x2 - x1);
}

void pad_with(vector<vector<float>>& array, int pad_width) {
    int rows = array.size();
    int cols = array[0].size();

    // Top padding
    for (int i = 0; i < pad_width; ++i) {
        array.insert(array.begin(), array[0]);
    }

    // Bottom padding
    for (int i = 0; i < pad_width; ++i) {
        array.push_back(array[rows - 1]);
    }

    // Left and right padding
    for (int i = 0; i < rows + 2 * pad_width; ++i) {
        for (int j = 0; j < pad_width; ++j) {
            array[i].insert(array[i].begin(), array[i][0]);
            array[i].push_back(array[i][cols - 1]);
        }
    }
}

float interpolate(const vector<vector<float>>& img, float x, float y) {
   
    int x1 = floor(x);
    int x2 = ceil(x);
    int y1 = floor(y);
    int y2 = ceil(y);

    if (x1 == x2 && y1 == y2) {
        return img[y1][x1];
    } else if (x1 == x2) {
        return img[y1][x1] + (y - y1) * calculate_slope(y1, img[y1][x1], y2, img[y2][x1]);
    } else if (y1 == y2) {
        return img[y1][x1] + (x - x1) * calculate_slope(x1, img[y1][x1], x2, img[y1][x2]);
    } else {
        float Q11 = img[y1][x1];
        float Q12 = img[y2][x1];
        float Q21 = img[y1][x2];
        float Q22 = img[y2][x2];

        float slope_y1 = calculate_slope(x1, Q11, x2, Q21);
        float slope_y2 = calculate_slope(x1, Q12, x2, Q22);
        float interpolated_y1 = Q11 + (x - x1) * slope_y1;
        float interpolated_y2 = Q12 + (x - x1) * slope_y2;

        float slope_x = calculate_slope(y1, interpolated_y1, y2, interpolated_y2);
        return interpolated_y1 + (y - y1) * slope_x;
    }
}


vector<vector<vector<float>>> demosaic(const vector<vector<float>>& img, pair<int, int> kernel_size = {6, 6}) {
    int rows = img.size();
    int cols = img[0].size();
    
    if (rows == 0 || cols == 0) {
        throw invalid_argument("Input image must be non-empty");
    }

    vector<vector<float>> padded_img = img;
    pad_with(padded_img, kernel_size.first);

    int H_pad = padded_img.size();
    int W_pad = padded_img[0].size();

    int channels = kernel_size.first * kernel_size.second;
    vector<vector<vector<float>>> processed_img(rows, vector<vector<float>>(cols, vector<float>(channels, 0)));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int ki = 0; ki < kernel_size.first; ++ki) {
                for (int kj = 0; kj < kernel_size.second; ++kj) {
                    float x = j + kj + 0.5f;
                    float y = i + ki + 0.5f;
                    processed_img[i][j][ki * kernel_size.second + kj] = interpolate(padded_img, x, y);
                }
            }
        }
    }

    return processed_img;
}

vector<vector<float>> average_channels(const vector<vector<vector<float>>>& img) {
    int rows = img.size();
    int cols = img[0].size();
    int channels = img[0][0].size();
    printf("rows: %d, cols: %d, channels: %d\n", rows, cols, channels);

    vector<vector<float>> averaged_img(rows, vector<float>(cols, 0.0f));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float sum = 0.0f;
            for (int c = 0; c < channels; ++c) {
                sum += img[i][j][c];
            }
            averaged_img[i][j] = sum / channels;
        }
    }

    return averaged_img;
}

void save_to_raw(const vector<vector<float>>& img, const string& filename) {
    ofstream file(filename, ios::out | ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Could not open file for writing");
    }

    for (const auto& row : img) {
        file.write(reinterpret_cast<const char*>(row.data()), row.size() * sizeof(float));
    }

    file.close();
}


int main() {

    FILE *file = fopen("/home/jyang/code/test_data/dm_input.raw", "rb");
    if (!file) {
        throw runtime_error("Could not open file for reading");
    }
    // 存入 uint_16 数组
    uint16_t *img_16 = new uint16_t [height * width];
    fread(img_16, sizeof(uint16_t), height * width, file);
    fclose(file);

    // 转换为 float 数组
    vector<vector<float>> img(height, vector<float>(width, 0.0f));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            img[i][j] = img_16[i * width + j];
        }
    }

    vector<vector<vector<float>>> processed_img = demosaic(img);
    vector<vector<float>> averaged_img = average_channels(processed_img);

    save_to_raw(averaged_img, "/home/jyang/code/test_data/out_float.raw");

    return 0;
}
