#ifndef ST_TEST_HPP
#define ST_TEST_HPP


#include <iostream>
#include <string>

// 模块基类模板
template<typename Input, typename Output>
class Module {
public:
    virtual Output process(const Input& input) = 0;
    virtual ~Module() {}
};

// 模块类模板
template<typename Input, typename Output>
class ConcreteModule : public Module<Input, Output> {
public:
    Output process(const Input& input) override {
        std::cout << "Processing input: " << input << std::endl;
        // 具体的处理逻辑
        return Output();
    }
};

// 特化模块类模板为不同类型的输入和输出
template<>
class ConcreteModule<int, std::string> : public Module<int, std::string> {
public:
    std::string process(const int& input) override {
        std::cout << "Processing int input: " << input << std::endl;
        // 具体的处理逻辑
        return "Processed int";
    }
};

template<>
class ConcreteModule<double, bool> : public Module<double, bool> {
public:
    bool process(const double& input) override {
        std::cout << "Processing double input: " << input << std::endl;
        // 具体的处理逻辑
        return true;
    }
};


#endif // ST_TEST_HPP
