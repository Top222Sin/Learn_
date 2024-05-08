cmake_minimum_required(VERSION 3.16.0)

project(testDemo VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)          # 设置 C++ 标准为 C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 确保编译器支持 C++20
set(CMAKE_CXX_EXTENSIONS OFF)       # 关闭编译器特定的扩展，使用标准 C++


find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)


# find_package(ncnn REQUIRED)
# include(${nlopt_DIR}/NLoptConfig.cmake)
# message(STATUS "nlopt_DIR: ${nlopt_DIR}")
# message(STATUS "NLOPT_INCLUDE_DIRS: ${NLOPT_INCLUDE_DIRS}")
# message(STATUS "NLOPT_LIBRARY_DIRS: ${NLOPT_LIBRARY_DIRS}")

include(${opencv_DIR}/OpenCVConfig.cmake)
# message(STATUS "opencv_DIR: ${opencv_DIR}")
# message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
# message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")

if("${OpenCV_LIBS}" STREQUAL "")
    set(OpenCV_FOUND FALSE)
endif()
if(NOT OpenCV_FOUND)
    find_package(OpenCV QUIET COMPONENTS core highgui imgproc imgcodecs videoio photo)
endif()
if(NOT OpenCV_FOUND)
    find_package(OpenCV QUIET COMPONENTS core highgui imgproc)
endif()

set(EIGEN_INCLUDE_DIR ThirdLibs/eigen3)
message(STATUS "EIGEN_INCLUDE_DIR: ${EIGEN_INCLUDE_DIR}")


set(headers
    ${EIGEN_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    )

set(sources
    ./src/st_test.cpp
    )

include_directories( ${headers})

add_executable(testDemo ${headers} ${sources})

target_link_libraries(testDemo PUBLIC Threads::Threads benchmark::benchmark)

if(OpenCV_FOUND)
    target_link_libraries(testDemo PRIVATE ${OpenCV_LIBS})
endif()

target_include_directories(testDemo PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                                        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
                                        $<INSTALL_INTERFACE:include>)
target_include_directories(testDemo PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                                        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                                        $<INSTALL_INTERFACE:include>
                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                                        )

target_include_directories(
  testDemo PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)


