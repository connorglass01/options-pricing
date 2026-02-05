cmake_minimum_required(VERSION 4.2.1)

project(price)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
                "src/main.cpp"
                "src/engines.cpp"
                "include/pricing/engines.h"
                "include/pricing/types.h"
                "include/rng/Random.h"
                "src/cli.cpp"
                "include/cli/cli.h"
            )

set(CMAKE_BUILD_TYPE Release)