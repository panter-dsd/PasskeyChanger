set (PROJECT_OUTPUT_NAME PasskeyChanger)
project(${PROJECT_OUTPUT_NAME})

cmake_minimum_required( VERSION 2.6 )

INCLUDE(FindQt4)
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE})
add_definitions(-DUNICODE)

include_directories(
src
${CMAKE_CURRENT_BINARY_DIR}
)

################################################################
# src
################################################################

set (src_SRC
src/main.cpp
src/mainwindow.cpp
src/torrentfilepasskeychanger.cpp
src/torrentdirpasskeychanger.cpp
src/qbittorrentpasskeychanger.cpp
)

set (src_HEADERS
src/mainwindow.h
src/abstractpasskeychanger.h
src/torrentfilepasskeychanger.h
src/torrentdirpasskeychanger.h
src/qbittorrentpasskeychanger.h
)

set (src_UI
src/mainwindow.ui
)

################################################################
# all
################################################################
set(
SOURCES
${src_SRC}
)

set(
HEADERS
${src_HEADERS}
)

set (UI
${src_UI}
)

qt4_wrap_ui( UI_HEADERS ${UI} )

qt4_wrap_cpp( MOC_SOURCES ${HEADERS} )

set( RESOURCES resource.qrc )

qt4_add_resources( QRC_SOURCES ${RESOURCES} )

add_executable( ${PROJECT_OUTPUT_NAME} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${UI_HEADERS})

target_link_libraries( ${PROJECT_OUTPUT_NAME} ${QT_LIBRARIES} )
