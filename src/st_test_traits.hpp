#ifndef ST_TEST_TRAITS_HPP
#define ST_TEST_TRAITS_HPP

#include <iostream>
#include <string>
#include <type_traits>

// 假设的输出类型定义
struct SomeOutputType {
    // 输出类型的具体实现细节
};

struct SomeOtherOutputType {
    // 另一个输出类型的具体实现细节
};

// 示例类型定义
struct TypeA {
    int valueForA;
};

struct TypeB {
    float valueForB;
};


// 假设的基础模块类
template<typename Input, typename Output>
class Module {
public:
    virtual ~Module() {}
    virtual Output process(const Input& input) = 0;
};

// 类型traits帮助类，用于检测Input类型
template<typename T>
struct InputTraits {};

// 对TypeA的特化
template<>
struct InputTraits<TypeA> {
    static void ProcessInput(const TypeA& input) {
        // 处理TypeA类型的输入
        std::cout << "InputTraits::Processing TypeA input: " << input.valueForA << std::endl;
    }
};

// 对TypeB的特化
template<>
struct InputTraits<TypeB> {
    static void ProcessInput(const TypeB& input) {
        // 处理TypeB类型的输入
        std::cout << "InputTraits::Processing TypeB input: " << input.valueForB << std::endl;
    }
};

// 模块类模板
template<typename Input, typename Output>
class ConcreteModule : public Module<Input, Output> {
public:
    Output process(const Input& input) override {
        
        // 使用类型traits进行处理
        InputTraits<Input>::ProcessInput(input);

        // 根据Input类型的不同，这里的Output逻辑也可以分开处理
        if constexpr (std::is_same_v<Input, TypeA>) {
            
            // 对TypeA输入的特定Output逻辑
            printf("is_same_v::Processing TypeA input: %d\n", input.valueForA);
            return Output{/* 根据TypeA计算Output */};
        } else if constexpr (std::is_same_v<Input, TypeB>) {
            
            // 对TypeB输入的特定Output逻辑
            printf("is_same_v::Processing TypeB input: %f\n", input.valueForB);
            return Output{/* 根据TypeB计算Output */};
        } else {
            
            // 默认处理逻辑或抛出异常
            throw std::runtime_error("Unsupported input type");
        }
    }
};








#endif // ST_TEST_TRAITS_HPP

