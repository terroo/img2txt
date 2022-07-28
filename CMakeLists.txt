cmake_minimum_required(VERSION 3.5)
project(Img2Txt VERSION 0.1 LANGUAGES CXX)

if(NOT DEFINED QT_DIR_VER)
  message(FATAL_ERROR "Set the variable: QT_DIR_VER .")
else()
  string(FIND ${QT_DIR_VER} "6\." posqt)
  string(SUBSTRING ${QT_DIR_VER} 0 ${posqt} dirqt)
  string(SUBSTRING ${QT_DIR_VER} ${posqt} 5 ver)
  set(CMAKE_PROJECT_INCLUDE_BEFORE "${dirqt}Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake")
  set(CMAKE_PREFIX_PATH "${dirqt}${ver}/gcc_64")
endif()

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
  qt_add_executable(Img2Txt
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
  )
  qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
  if(ANDROID)
    add_library(Img2Txt SHARED
      ${PROJECT_SOURCES}
    )
  else()
    add_executable(Img2Txt
      ${PROJECT_SOURCES}
    )
  endif()

  qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Img2Txt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS} -llept -ltesseract)

set_target_properties(Img2Txt PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(Img2Txt)
endif()

add_custom_command(
  TARGET Img2Txt
  POST_BUILD
  COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/resources/genbin.sh "${CMAKE_PREFIX_PATH}"
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/resources/img DESTINATION
  /usr/share/pixmaps/img2txt)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/resources/img/img2txt.png DESTINATION 
  /usr/share/pixmaps)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/resources/img2txt.desktop DESTINATION
  /usr/share/applications)
install(TARGETS Img2Txt DESTINATION /opt/img2txt)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/img2txt DESTINATION bin)

add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
  TARGET "uninstall"
  POST_BUILD
  COMMENT "Uninstall files with install_manifest.txt"
  COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in install_manifest.txt to be uninstalled!
  COMMAND rm -rf /usr/share/pixmaps/img2txt
  COMMAND rm -rf /opt/img2txt
  #COMMAND rm /usr/local/bin/img2txt
)

