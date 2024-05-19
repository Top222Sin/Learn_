
#include "st_test_gtest.hpp"

#include <Eigen/Dense>

#include <gtest/gtest.h>

// 要测试的函数
int add(int a, int b) {
    return a + b;
}

// 测试用例
TEST(AddTest, PositiveNumbers) {
    // 预期结果
    int expected = 5;

    // 实际结果
    int result = add(2, 3);

    // 断言
    ASSERT_EQ(expected, result);
}

TEST(AddTest, NegativeNumbers) {
    // 预期结果
    int expected = -5;

    // 实际结果
    int result = add(-2, -3);

    // 断言
    ASSERT_EQ(expected, result);
}

TEST(AddTest, SumNumbers) {
    // 预期结果
    int expected = 0;

    // 实际结果
    int result = add(-2, 2);

    // 断言
    ASSERT_EQ(expected, result);
}

template <typename T>
void testMatrixMultiply() {
    Eigen::Matrix<T, 2, 3> mat1;
    Eigen::Matrix<T, 3, 2> mat2;

    // 初始化矩阵 mat1
    mat1 << 1, 2, 3,
            4, 5, 6;

    // 初始化矩阵 mat2
    mat2 << 7, 8,
            9, 10,
            11, 12;

    // 预期的结果矩阵
    Eigen::Matrix<T, 2, 2> expected;
    expected << 58, 64,
                139, 154;

    // 执行矩阵乘法
    Eigen::Matrix<T, 2, 2> result = matrixMultiply<T, 2, 3, 2>(mat1, mat2);

    // 检查结果是否与预期相符
    EXPECT_TRUE(result.isApprox(expected));
}

// 测试 int 类型的矩阵乘法
TEST(MatrixMultiplyTest, HandlesInt) {
    testMatrixMultiply<int>();
}

// 测试 double 类型的矩阵乘法
TEST(MatrixMultiplyTest, HandlesDouble) {
    testMatrixMultiply<double>();
}

// 测试 float 类型的矩阵乘法
TEST(MatrixMultiplyTest, HandlesFloat) {
    testMatrixMultiply<double>();
}



int main(int argc, char** argv) {
    // 初始化测试框架
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}