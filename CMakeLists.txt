cmake_minimum_required(VERSION 3.0.0)
project(BezierCurveDemo VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# copy asssets folder into build
# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_library(bezierCurve BezierCurve.cpp BezierCurve.hpp)
target_link_libraries(bezierCurve ${SDL2_LIBRARIES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} bezierCurve)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
