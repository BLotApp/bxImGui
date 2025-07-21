cmake_minimum_required(VERSION 3.10)

set(ADDON_NAME "bxImGui")

add_library(${ADDON_NAME} STATIC
    bxImGui.cpp
    bxImGui.h
)

# bxImGui depends on blot core
target_link_libraries(${ADDON_NAME} PUBLIC blot)

target_include_directories(${ADDON_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    ${CMAKE_CURRENT_LIST_DIR}/imgui
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends
)

# ------------------------------------------------------------------
# Local third-party libs
# ------------------------------------------------------------------
add_subdirectory(third_party/ImGuizmo EXCLUDE_FROM_ALL)
add_subdirectory(third_party/implot   EXCLUDE_FROM_ALL)

# ImGuizmo & ImPlot provide targets ImGuizmo / implot
# ImPlot3D is header-only

target_link_libraries(${ADDON_NAME} PUBLIC ImGuizmo implot)

target_include_directories(${ADDON_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/third_party/IconFontCppHeaders>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/third_party/implot3d>
)

# Build examples for this addon (optional)
option(BUILD_BXIMGUI_EXAMPLES "Build bxImGui examples" OFF)
if(BUILD_BXIMGUI_EXAMPLES AND EXISTS "${CMAKE_CURRENT_LIST_DIR}/examples")
    add_subdirectory(examples)
endif()

message(STATUS "Configured addon: ${ADDON_NAME}") 
