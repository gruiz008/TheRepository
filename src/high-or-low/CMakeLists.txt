cmake_minimum_required(VERSION 3.31)
project(high_or_low)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(high_or_low main.cpp
        stdstrhelper.cpp
        sdtstrhelper.h
        stringconstants.h
        roll_game.cpp
        roll_game.h)


# Find our pre-installed DPP package (using FindDPP.cmake).
find_package(DPP REQUIRED)
target_compile_definitions(${PROJECT_NAME} PUBLIC DPP_CORO=1)

# Link the pre-installed DPP package.
target_link_libraries(${PROJECT_NAME}
        ${DPP_LIBRARIES}
)

# Include the DPP directories.
target_include_directories(${PROJECT_NAME} PRIVATE
        ${DPP_INCLUDE_DIR}
)

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)