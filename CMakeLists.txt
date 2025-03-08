cmake_minimum_required(VERSION 3.21)

set(CMAKE CXX_STANDARD 17)

project(thread_pool)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(. SRC_LIST)
add_executable(thread_pool ${SRC_LIST})
