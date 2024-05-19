#ifndef ST_TEST_GTEST_HPP
#define ST_TEST_GTEST_HPP

#include <iostream>
#include <Eigen/Dense>

template <typename T, int rows1, int cols1, int cols2>
Eigen::Matrix<T, rows1, cols2> matrixMultiply(const Eigen::Matrix<T, rows1, cols1>& mat1, const Eigen::Matrix<T, cols1, cols2>& mat2) {
    return mat1 * mat2;
}

// int main() {
//     Eigen::Matrix<float, 2, 3> mat1;
//     mat1 << 1, 2, 3,
//             4, 5, 6;

//     Eigen::Matrix<float, 3, 2> mat2;
//     mat2 << 7, 8,
//             9, 10,
//             11, 12;

//     Eigen::Matrix<float, 2, 2> result = matrixMultiply(mat1, mat2);

//     std::cout << "Result:\n" << result << std::endl;

//     return 0;
// }

#endif // ST_TEST_GTEST_HPP
