cmake_minimum_required(VERSION 3.0.0)
project(zaliczenie VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB zaliczenie_src "*.hpp" "*.cpp")

add_executable(zaliczenie ${zaliczenie_src})
#set_target_properties(zaliczenie PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
