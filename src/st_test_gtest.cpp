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



int main(int argc, char** argv) {
    // 初始化测试框架
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}