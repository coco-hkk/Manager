cmake_minimum_required(VERSION 3.16)

project(Manager LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.2 COMPONENTS Quick Network Core5Compat LinguistTools REQUIRED)

include(Imageviewer/CMakeLists.txt)

qt_add_executable(Manager MANUAL_FINALIZATION
    main.cpp
    ${SOURCES}
)
qt_finalize_target(Manager)

qt_add_qml_module(Manager
    URI Manager
    VERSION 1.0
    RESOURCE_PREFIX /
    QML_FILES
        main.qml
)

set_target_properties(Manager PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(Manager
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Manager PUBLIC
    Qt6::Quick
    Qt6::Core
    ${LINK_LIBRARIES})
