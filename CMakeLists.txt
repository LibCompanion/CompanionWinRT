# Define CMake minimum version
cmake_minimum_required(VERSION 3.7)


# Use Universal Windows Platform as target system
set(CMAKE_SYSTEM_NAME "WindowsStore")
set(CMAKE_SYSTEM_VERSION "10.0")


# Set installation directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory")


# Configure CMake project
project(CompanionWinRT)


# Define CMake Flags
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)
set(CMAKE_DEBUG_POSTFIX "D")


# Configure dependencies
set(OpenCVComponents "core" "imgproc" "imgcodecs" "features2d" "videoio" "calib3d")
find_package(OpenCV REQUIRED ${OpenCVComponents})
find_package(Companion REQUIRED)


# Configure CompanionWinRT
add_subdirectory(CompanionWinRT)
target_include_directories(CompanionWinRT PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:include>  # <prefix>/include
)


# Configure additional modules
#ExternalProject_Add(<name> [<option>...])


# Copy the samples to the build folder
file(COPY samples/CompanionUWPSample DESTINATION .)