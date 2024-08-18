cmake_minimum_required(VERSION 3.22)
project(ChatChido)

add_executable(ChatChido myApplication.cpp chat.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

target_link_libraries(ChatChido ${GTKMM_LIBRARIES})
