cmake_minimum_required(VERSION 3.5)

project(img2txt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package( OpenCV REQUIRED )

set(TS_FILES img2txt_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        window.cpp
        window.hpp
        window.ui
        img2txt.hpp
        img2txt.cpp
        ${TS_FILES}
)

include_directories( ${OpenCV_INCLUDE_DIRS} )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(img2txt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET img2txt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(img2txt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(img2txt
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(img2txt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS} -llept -ltesseract)

set_target_properties(img2txt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(img2txt)
endif()

add_custom_command(
    TARGET img2txt
    POST_BUILD
    COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/resources/generate.sh
)

# make install
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/resources/img DESTINATION
  /usr/share/pixmaps/img2txt)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/resources/img/img2txt.png DESTINATION 
  /usr/share/pixmaps)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/img2txt.desktop DESTINATION
  /usr/share/applications)
install(TARGETS img2txt DESTINATION bin)

# make uninstall
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in install_manifest.txt to be uninstalled!
    COMMAND rm -rf /usr/share/pixmaps/img2txt
    #COMMAND rm /usr/share/applications/img2txt.desktop
)

