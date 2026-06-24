cmake_minimum_required(VERSION 3.15)

#------------SETTINGS--------------------------------------------------------------------------

#GPU Acceleration
option(USE_GPU ON) #ON/OFF

#build folder of the CPU version of Release OpenCV 4.13
set(OpenCV_DIR "C:/Users/kouro/Documents/Prog/C_C++/_Libs/opencv4.13/build")

#If GPU acceleration enabled "build_cuda/install" folder location
if(USE_GPU)
set(OpenCV_DIR "C:/Users/kouro/Documents/Prog/C_C++/_Libs/opencv4.13_GPU/build_cuda/install")
endif()

#Source files to compile
file(GLOB_RECURSE sourcesfiles "src/chapter6.cpp")

#----------------------------------------------------------------------------------------------

project(
computer_vision_learning 
VERSION 1.0
DESCRIPTION "First approach to computer vision. Will feature image, video and live video analysis."
LANGUAGES CXX
)

#-----------------------------------------------------------------------------
#Get rid of the policy warning for GPU Accelerated OpenCV (by Gemini)
set(CMAKE_WARN_DEPRECATED OFF)
if(POLICY CMP0146)
    cmake_policy(SET CMP0146 OLD)
endif()
set(CMAKE_WARN_DEPRECATED ON)
#-----------------------------------------------------------------------------

add_executable(testOpenCV ${sourcesfiles})

#CMake docs (copy folder every time I build)
add_custom_command(
TARGET testOpenCV 
POST_BUILD
COMMAND ${CMAKE_COMMAND} 
-E copy_directory
"${CMAKE_CURRENT_SOURCE_DIR}/assets" #Origin
"${CMAKE_CURRENT_BINARY_DIR}/assets" #Destination
)

if(USE_GPU)
    message(STATUS "\n\n             --- Building with GPU Accelerated OpenCV 4.13 ---\n\n")
else()
    message(STATUS "\n\n             --- Building with CPU OpenCV 4.13 ---\n\n\n")
endif()

#-----------------------------------------------
#Adding pre-built OpenCV library to the project (https://github.com/opencv/opencv/releases/tag/4.13.0)

# Based on - https://stackoverflow.com/a/44218752
# Posted by 姚嘉辉, modified by community. See post 'Timeline' for change history
# Retrieved 2026-06-21, License - CC BY-SA 4.0
# Note: Adapted for local OpenCV 4.13 path and project-specific requirements.
find_package(OpenCV 4.13 REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
if(OPENCV_FOUND)
target_include_directories(testOpenCV PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(testOpenCV ${OpenCV_LIBS})
else()
message(STATUS "\n\n             --- Could not open OpenCV ---\n\n\n")
endif()
#-----------------------------------------------