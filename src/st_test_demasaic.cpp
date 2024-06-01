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

void pad_with_zero(vector<vector<float>>& array, int pad_width) {
    int rows = array.size();
    int cols = array[0].size();

    // 创建一个新的填充后的图像数组，大小为 (rows + 2 * pad_width) x (cols + 2 * pad_width)
    vector<vector<float>> padded_array(rows + 2 * pad_width, vector<float>(cols + 2 * pad_width, 0));

    // 复制原始数组到填充后的数组中心
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            padded_array[i + pad_width][j + pad_width] = array[i][j];
        }
    }

    // 用0填充完成的数组赋值回原始数组
    array.swap(padded_array);
}

void reflect_pad(vector<vector<float>>& array, int pad_width) {
    int rows = array.size();
    int cols = array[0].size();

    // 创建一个新的填充后的图像数组
    vector<vector<float>> padded_array(rows + 2 * pad_width, vector<float>(cols + 2 * pad_width, 0));

    // 复制原始数组到填充后的数组中心
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            padded_array[pad_width + i][pad_width + j] = array[i][j];
        }
    }

    // 顶部填充（反射填充）
    for (int i = 0; i < pad_width; ++i) {
        for (int j = 0; j < cols + 2 * pad_width; ++j) {
            padded_array[pad_width - 1 - i][j] = padded_array[2 * (pad_width - 1 - i) + 1 + pad_width][j];
        }
    }

    // 底部填充（反射填充）
    for (int i = rows + pad_width; i < rows + 2 * pad_width; ++i) {
        for (int j = 0; j < cols + 2 * pad_width; ++j) {
            padded_array[i][j] = padded_array[2 * (rows + pad_width - 1) - i][j];
        }
    }

    // 左侧和右侧填充（反射填充）
    for (int i = 0; i < rows + 2 * pad_width; ++i) {
        for (int j = 0; j < pad_width; ++j) {
            padded_array[i][pad_width - 1 - j] = padded_array[i][2 * (pad_width - 1 - j) + 1 + pad_width];
        }
        for (int j = cols + pad_width; j < cols + 2 * pad_width; ++j) {
            padded_array[i][j] = padded_array[i][2 * (cols + pad_width - 1) - j];
        }
    }

    // 用填充后的数组赋值回原始数组
    array.swap(padded_array);
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
   
    int x1 = std::floor(x);
    int x2 = std::ceil(x);
    int y1 = std::floor(y);
    int y2 = std::ceil(y);

    if (x1 < 0 || x2 >= img[0].size() || y1 < 0 || y2 >= img.size()) {
        return 0; // Handle out-of-bounds cases
    }

    float Q11 = img[y1][x1];
    float Q12 = img[y2][x1];
    float Q21 = img[y1][x2];
    float Q22 = img[y2][x2];

    float R1 = ((x2 - x) / (x2 - x1)) * Q11 + ((x - x1) / (x2 - x1)) * Q21;
    float R2 = ((x2 - x) / (x2 - x1)) * Q12 + ((x - x1) / (x2 - x1)) * Q22;

    float P = ((y2 - y) / (y2 - y1)) * R1 + ((y - y1) / (y2 - y1)) * R2;

    return P;
}


vector<vector<vector<float>>> demosaic(const vector<vector<float>>& img, pair<int, int> kernel_size = {6, 6}) {
    int rows = img.size();
    int cols = img[0].size();
    
    if (rows == 0 || cols == 0) {
        throw invalid_argument("Input image must be non-empty");
    }

    vector<vector<float>> padded_img = img;
    pad_with(padded_img, kernel_size.first);
    // pad_with_zero(padded_img, kernel_size.first);
    // reflect_pad(padded_img, kernel_size.first);
    
    // 打印 img 前20个元素
    printf("mademosaicin :: padded_img\n");
    for (int i = 0; i < 20; ++i) {
        cout << padded_img[0][i] << " ";
    }
    cout << endl;

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

    // 打印 processed_img 前20个元素
    printf("mademosaicin :: processed_img\n");
    for (int i = 0; i < 20; ++i) {
        cout << processed_img[0][0][i] << " ";
    }
    cout << endl;

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

    // 打印 averaged_img 前20个元素
    printf("average_channels :: averaged_img\n");
    for (int i = 0; i < 20; ++i) {
        cout << averaged_img[0][i] << " ";
    }
    cout << endl;

    return averaged_img;
}

void save_to_raw(const vector<vector<float>>& img, const string& filename) {
    ofstream file(filename, ios::out | ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Could not open file for writing");
    }

    // 打印 img 前20个元素
    printf("save_to_raw :: img\n");
    for (int i = 0; i < 20; ++i) {
        cout << img[0][i] << " ";
    }
    cout << endl;

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

    // 打印 img 前20个元素
    printf("main :: img\n");
    for (int i = 0; i < 20; ++i) {
        cout << img[0][i] << " ";
    }
    cout << endl;


    vector<vector<vector<float>>> processed_img = demosaic(img);
    vector<vector<float>> averaged_img = average_channels(processed_img);

    save_to_raw(averaged_img, "/home/jyang/code/test_data/out_float.raw");

    return 0;
}
