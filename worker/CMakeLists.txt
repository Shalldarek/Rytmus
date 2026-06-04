cmake_minimum_required(VERSION 3.15)
project(RytmusWorker CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(CPR_BUILD_TESTS OFF)
set(BUILD_TESTING OFF)
set(WERROR ON) 

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1.11.1  
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(worker main.cpp)
target_link_libraries(worker PRIVATE cpr::cpr nlohmann_json::nlohmann_json)