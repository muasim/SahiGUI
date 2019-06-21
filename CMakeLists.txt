cmake_minimum_required(VERSION 3.9.0)

project(SAHIGUI)
set(DEPENDENCY_PATH ${CMAKE_SOURCE_DIR}/deps)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui/) # 3.9 requirements

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets 3DCore 3DExtras 3DRender 3DInput Charts MultimediaWidgets)
# include necessary qt3d modules

#find_package(FFmpeg REQUIRED COMPONENTS AVCODEC AVFORMAT AVUTIL AVDEVICE)
#include_directories(${FFMPEG_INCLUDE_DIRS})
find_package(LIBVLC REQUIRED)
include_directories(${LIBVLC_INCLUDE_DIRS})

include_directories(src)
# Populate a CMake variable with the sources
set(SAHIGUI_SRC
ui/main.ui
src/main.cpp
src/orbittransformcontroller.cpp
src/videoplayer.cpp
)
# Tell CMake to create the SahiKontrol executable
add_executable(${CMAKE_PROJECT_NAME}  ${SAHIGUI_SRC})

include_directories(${DEPENDENCY_PATH}/whereami-cpp/include)
add_library(whereami STATIC 
    ${DEPENDENCY_PATH}/whereami-cpp/source/whereami++.cpp
    ${DEPENDENCY_PATH}/whereami-cpp/source/whereami.c)
#MinGW workaround to set minimum required windows version
if(WIN32)
target_compile_definitions( whereami PUBLIC _WIN32_WINNT=_WIN32_WINNT_WINXP)
endif()
target_link_libraries(${PROJECT_NAME} whereami)
add_dependencies(${PROJECT_NAME} whereami)

target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBVLC_LIBRARIES})
# Use the Widgets module from Qt 5
target_link_libraries(
    ${CMAKE_PROJECT_NAME} 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::3DCore
    Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
    Qt5::Charts
    Qt5::MultimediaWidgets)