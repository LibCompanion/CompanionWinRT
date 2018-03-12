#
# CompanionWinRT is a Windows Runtime wrapper for Companion.
# Copyright (C) 2017-2018 Dimitri Kotlovsky, Andreas Sekulski
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

# Add source files
SET(SOURCE
    Configuration.cpp Configuration.h
    algo/detection/ShapeDetection.cpp algo/detection/ShapeDetection.h
    algo/recognition/hashing/LSH.cpp algo/recognition/hashing/LSH.h
    algo/recognition/matching/FeatureMatching.cpp algo/recognition/matching/FeatureMatching.h
    draw/Frame.cpp draw/Frame.h
    model/processing/FeatureMatchingModel.cpp model/processing/FeatureMatchingModel.h
    model/result/Result.cpp model/result/Result.h
    processing/detection/ObjectDetection.cpp processing/detection/ObjectDetection.h
    processing/recognition/MatchRecognition.cpp processing/recognition/MatchRecognition.h
    processing/recognition/HashRecognition.cpp processing/recognition/HashRecognition.h
    processing/recognition/HybridRecognition.cpp processing/recognition/HybridRecognition.h
    input/ImageStream.cpp input/ImageStream.h
    utils/CompanionError.h
    utils/CompanionUtils.cpp utils/CompanionUtils.h
)


# Create MSVC filter
foreach(source IN LISTS SOURCE)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()


# Create library and define it as a WinRT Component
add_library(CompanionWinRT SHARED ${SOURCE})
set_target_properties(CompanionWinRT PROPERTIES VS_WINRT_COMPONENT TRUE)
set_target_properties(CompanionWinRT PROPERTIES VS_GLOBAL_ROOTNAMESPACE "CompanionWinRT")
set_target_properties(CompanionWinRT PROPERTIES FOLDER "CompanionWinRT")


# Set linked libraries
target_link_libraries(CompanionWinRT ${OpenCV_LIBS})
target_link_libraries(CompanionWinRT Companion)


# add install instructions
install(TARGETS CompanionWinRT EXPORT CompanionWinRTConfig
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h")
install(EXPORT CompanionWinRTConfig DESTINATION "lib")
