set (PROJECT_OUTPUT_NAME passkeychanger)
project(PasskeyChanger)

cmake_minimum_required( VERSION 2.6 )

INCLUDE(FindQt4)
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE})
add_definitions(-DUNICODE)

include_directories(
src
src/dialogs
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
# dialogs
################################################################

set (dialogs_SRC
src/dialogs/aboutdialog.cpp
)

set (dialogs_HEADERS
src/dialogs/aboutdialog.h
)

set (dialogs_UI
)

################################################################
# all
################################################################
set(
SOURCES
${src_SRC}
${dialogs_SRC}
)

set(
HEADERS
${src_HEADERS}
${dialogs_HEADERS}
)

set (UI
${src_UI}
${dialogs_UI}
)

qt4_wrap_ui( UI_HEADERS ${UI} )

qt4_wrap_cpp( MOC_SOURCES ${HEADERS} )

set( RESOURCES resource.qrc )

qt4_add_resources( QRC_SOURCES ${RESOURCES} )

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
	add_executable( ${PROJECT_OUTPUT_NAME} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${UI_HEADERS})
else()
	add_executable( ${PROJECT_OUTPUT_NAME} WIN32 ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${UI_HEADERS})
endif()

target_link_libraries( ${PROJECT_OUTPUT_NAME} ${QT_LIBRARIES} )
