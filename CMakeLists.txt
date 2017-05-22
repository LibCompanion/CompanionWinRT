#
# This program is a Windows Runtime wrapper for the Companion CV library.
#          https://github.com/LibCompanion/libCompanion
#
# Copyright (C) 2017 Dimitri Kotlovsky
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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
#set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D _CRT_SECURE_NO_WARNINGS")
set(Companion_USE_CUDA OFF CACHE BOOL "Use cuda implementation of libCompanion" FORCE)


# Define global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Configure dependencies
set(OpenCVComponents "core" "imgproc" "imgcodecs" "features2d" "videoio" "calib3d")
find_package(OpenCV REQUIRED ${OpenCVComponents})


# Configure CompanionWinRT
add_subdirectory(libCompanion)
add_subdirectory(CompanionWinRT)
target_include_directories(CompanionWinRT PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:include>  # <prefix>/include
)


# Copy the samples to the build folder
file(COPY samples/CompanionUWPSample DESTINATION .)
