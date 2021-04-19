cmake_minimum_required(VERSION 3.14)

project(video_editor LANGUAGES CXX)

add_compile_options(-fPIC)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED Core Qml Quick Widgets)
find_package(OpenCV REQUIRED)

set(QT_LIBRARIES Qt5::Core Qt5::Qml Qt5::Quick Qt5::Widgets)

include_directories(
    include
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Qml_INCLUDE_DIRS}
    ${Qt5Quick_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)
set(QT_HEADERS
    include/overlayfactory.h
    include/thumbnailitem.h
    include/videomodel.h
    include/videothread.h
    )
set(QT_SOURCES
    src/overlayfactory.cpp
    src/thumbnailitem.cpp
    src/videomodel.cpp
    src/videothread.cpp
)
set(SOURCES
    src/main.cpp
    src/overlaybase.cpp
    src/overlaynumber.cpp
    src/overlayrect.cpp
    src/overlayslider.cpp
)

QT5_ADD_RESOURCES(QML_QRC qml/qml.qrc)
QT5_WRAP_CPP(QT_HEADERS_HPP ${QT_HEADERS})

add_executable(${PROJECT_NAME} ${SOURCES} ${QT_SOURCES} ${QT_HEADERS_HPP} ${QML_QRC})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${OpenCV_LIBRARIES})
