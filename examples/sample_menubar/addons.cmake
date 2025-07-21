# Addons required by sample_menubar
include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

# UI addon
CPMAddPackage(
    NAME bxImGui
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/addons/bxImGui
) 