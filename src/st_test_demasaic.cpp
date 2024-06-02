#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <string>
#include <utility>
#include <cstdint>
#include <cstdint>  // for uint16_t
#include <functional>

#include <numeric>

using namespace std;

int height = 1200;
int width = 1600;
int channels = 1;

// 填充函数
void pad_with(std::vector<std::vector<float>>& array, int pad_height, int pad_width) {
int H = array.size();
    int W = array[0].size();
    printf("pad_with::H: %d, W: %d\n", H, W);

    // 上下填充
    for (int i = 0; i < pad_height; ++i) {
        array.insert(array.begin(), array[0]); // 使用第一行填充上方
        array.push_back(array[H - 1]);         // 使用最后一行填充下方
    }

    H += 2 * pad_height;

    // 左右填充
    for (int i = 0; i < H; ++i) {
        // 左侧填充
        for (int k = 0; k < pad_width; ++k) {
            array[i].insert(array[i].begin(), array[i][0]); // 使用当前行的第一个元素填充左侧
        }
        // 右侧填充
        for (int k = 0; k < pad_width; ++k) {
            array[i].push_back(array[i][W - 1]); // 使用当前行的最后一个元素填充右侧
        }
    }

    // W += 2 * pad_width;
    printf("pad_with::H after padding: %d, W after padding: %d\n", H, W);
}

// 生成插值函数的结构
struct Interp2D {
    std::vector<float> x;
    std::vector<float> y;
    std::vector<std::vector<float>> values;

    Interp2D(const std::vector<float>& x, const std::vector<float>& y, const std::vector<std::vector<float>>& values)
        : x(x), y(y), values(values) {}

    float operator()(float xi, float yi) const {
        int ix = std::upper_bound(x.begin(), x.end(), xi) - x.begin() - 1;
        int iy = std::upper_bound(y.begin(), y.end(), yi) - y.begin() - 1;

        if (ix < 0 || ix >= x.size() - 1 || iy < 0 || iy >= y.size() - 1) {
            return 0; // 超出范围的情况，返回0或者适当的值
        }

        float x1 = x[ix], x2 = x[ix + 1];
        float y1 = y[iy], y2 = y[iy + 1];

        float Q11 = values[iy][ix];
        float Q12 = values[iy][ix + 1];
        float Q21 = values[iy + 1][ix];
        float Q22 = values[iy + 1][ix + 1];

        float R1 = ((x2 - xi) * Q11 + (xi - x1) * Q12) / (x2 - x1);
        float R2 = ((x2 - xi) * Q21 + (xi - x1) * Q22) / (x2 - x1);

        return ((y2 - yi) * R1 + (yi - y1) * R2) / (y2 - y1);
    }
};

// 主函数
std::vector<std::vector<std::vector<float>>> demosaic(const std::vector<std::vector<float>>& img, std::pair<int, int> kernel_size = {6, 6}) {
    std::cout << "demosaic::img.size: " << img.size() << " x " << img[0].size() << std::endl;

    // 填充图像
    std::vector<std::vector<float>> padded_img = img;
    pad_with(padded_img, kernel_size.first, kernel_size.second);
    int H_pad = padded_img.size();
    int W_pad = padded_img[0].size();
    std::cout << "H_pad: " << H_pad << std::endl;
    std::cout << "W_pad: " << W_pad << std::endl;

    std::vector<int> grid_x(W_pad - 2 * kernel_size.first);
    std::vector<int> grid_y(H_pad - 2 * kernel_size.second);
    std::iota(grid_x.begin(), grid_x.end(), kernel_size.first);
    std::iota(grid_y.begin(), grid_y.end(), kernel_size.second);
    printf("grid_x.size: %d, grid_y.size: %d\n", grid_x.size(), grid_y.size());

    // 打印 grid_x 和 grid_y 的前20个元素
    printf("grid_x: ");
    for (int i = 0; i < 20; ++i) {
        cout << grid_x[i] << " ";
    }
    cout << endl;

    printf("grid_y: ");
    for (int i = 0; i < 20; ++i) {
        cout << grid_y[i] << " ";
    }
    cout << endl;

    // 初始化处理后的图像
    std::vector<std::vector<std::vector<float>>> processed_img(grid_y.size(), std::vector<std::vector<float>>(grid_x.size(), std::vector<float>(kernel_size.first * kernel_size.second)));

    for (int i = 0; i < kernel_size.first; ++i) {
        for (int j = 0; j < kernel_size.second; ++j) {
            std::vector<std::vector<float>> current_pattern;

            for (int ki = i; ki < H_pad; ki += kernel_size.first) {
                std::vector<float> row;
                for (int kj = j; kj < W_pad; kj += kernel_size.second) {
                    row.push_back(padded_img[ki][kj]);
                }
                current_pattern.push_back(row);
            }

            // printf("current_pattern.size: %d x %d\n", current_pattern.size(), current_pattern[0].size());
            std::vector<float> x;
            std::vector<float> y;
            for (int kj = j; kj < W_pad; kj += kernel_size.second) {
                x.push_back(kj);
            }
            for (int ki = i; ki < H_pad; ki += kernel_size.first) {
                y.push_back(ki);
            }

            Interp2D interp_func(x, y, current_pattern);
            for (int k = 0; k < grid_y.size(); ++k) {
                for (int l = 0; l < grid_x.size(); ++l) {
                    float xi = grid_x[l] + 0.0f;
                    float yi = grid_y[k] + 0.0f;
                    processed_img[k][l][i * kernel_size.second + j] = interp_func(xi, yi);
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
    printf("average_channels::rows: %d, cols: %d, channels: %d\n", rows, cols, channels);

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

vector<vector<float>> average_channels(const vector<vector<float>>& img) {
    int rows = img.size();
    int cols = img[0].size();
    int channels = 36;
    printf("average_channels::rows: %d, cols: %d, channels: %d\n", rows, cols, channels);

    vector<vector<float>> averaged_img(rows, vector<float>(cols, 0.0f));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float sum = 0.0f;
            for (int c = 0; c < channels; ++c) {
                sum += img[i][j];
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


    std::pair<int, int> kernel_size = {6, 6};
    vector<vector<vector<float>>> processed_img = demosaic(img, kernel_size);
    printf("main::processed_img.size: %d x %d\n", processed_img.size(), processed_img[0].size());

    // // 对 processed_img 进行通道平均
    vector<vector<float>> averaged_img = average_channels(processed_img);
    save_to_raw(averaged_img, "/home/jyang/code/test_data/out_float.raw");

    return 0;
}
