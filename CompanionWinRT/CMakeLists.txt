# Eliminate deprecation errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D _CRT_SECURE_NO_WARNINGS")


# Add source files
SET(SOURCE
    Configuration.cpp Configuration.h
    algo/CPUFeatureMatching.cpp algo/CPUFeatureMatching.h
    model/FeatureMatchingModel.cpp model/FeatureMatchingModel.h
    processing/2D/ObjectDetection.cpp processing/2D/ObjectDetection.h
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


# Set linked libraries
target_link_libraries(CompanionWinRT ${OpenCV_LIBS})
target_link_libraries(CompanionWinRT Companion)


# add install instructions
install(TARGETS CompanionWinRT EXPORT CompanionWinRTWrapperConfig
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h")
install(EXPORT CompanionWinRTWrapperConfig DESTINATION "lib")
