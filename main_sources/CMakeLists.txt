cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)

project(MainProject LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

# CXXOPTS
CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.1
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

# FMT
CPMAddPackage(
  NAME fmt
  GIT_TAG 7.1.3
  GITHUB_REPOSITORY fmtlib/fmt
  OPTIONS "FMT_INSTALL YES" # Create an installable target
)

# CSV_PARSER
CPMAddPackage(
  NAME csv-parser
  GITHUB_REPOSITORY vincentlaucsb/csv-parser
  GIT_TAG master
)

# BOOST/ASIO
CPMAddPackage(
  NAME asio
  GITHUB_REPOSITORY boostorg/asio
  GIT_TAG boost-1.80.0
  OPTIONS "ASIO_BUILD_EXAMPLES NO" "ASIO_BUILD_TESTS NO" "ASIO_ENABLE_INSTALL YES"
)

# # GLAD
# CPMAddPackage(
#   NAME glad
#   GITHUB_REPOSITORY Dav1dde/glad
#   VERSION 0.1.33
# )

# # GLM
# CPMAddPackage(
#   NAME glm
#   GITHUB_REPOSITORY g-truc/glm
#   GIT_TAG 0.9.9.7
# )

# GLFW
# CPMFindPackage(
#     NAME glfw3
#     # GITHUB_REPOSITORY glfw/glfw
#     # GIT_TAG 3.3.2
#     URL https://github.com/glfw/glfw/releases/download/3.3.6/glfw-3.3.6.zip
#     VERSION 3.3
#     OPTIONS
#         "ENKITS_BUILD_EXAMPLES OFF"
#         "GLFW_BUILD_EXAMPLES OFF"
#         "GLFW_BUILD_TESTS ON"
#         "GLFW_BUILD_DOCS ON"
#         "GLFW_BUILD_INSTALL ON"
# )


# Source file grouping of visual studio and xcode
CPMAddPackage(
  NAME GroupSourcesByFolder.cmake
  GITHUB_REPOSITORY TheLartians/GroupSourcesByFolder.cmake
  VERSION 1.0
)

CPMAddPackage(
  NAME sfml
  GITHUB_REPOSITORY SFML/SFML
  GIT_TAG 2.5.x
)
set(SFML_STATIC_LIBRARIES TRUE) # To use static libraries inside the project
set_target_properties(sfml-system PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-network PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-graphics PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-window PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-audio PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# CPMAddPackage(
#   NAME imgui
#   GITHUB_REPOSITORY Pesc0/imgui-cmake
#   GIT_TAG master
# )

# CPMAddPackage(
#   NAME imgui-sfml
#   GITHUB_REPOSITORY eliasdaler/imgui-sfml
#   OPTION "IMGUI_SFML_BUILD_EXAMPLES OFF" "IMGUI_SFML_BUILD_TESTS OFF" "SFML_DIR ${SFML_DIR}"
#   GIT_TAG master
# )


CPMAddPackage(NAME MainLibraries SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../main_libraries)

# ---- Create standalone executable ----

# Some platforms need OpenGL. Most don't, because we are using the gl3w loader library.
find_package(OpenGL REQUIRED)

# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
# find_package(SFML REQUIRED) # We don't need to find SFML as it is already located after CPM Call


file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h")

add_executable(${PROJECT_NAME} ${sources} ${headers})


set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "alieninvadersretro")

if (WIN32)
find_package(SFML REQUIRED COMPONENTS graphics window system audio network)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network opengl32 csv
  winmm locallibraries)

endif (WIN32)

if (UNIX AND NOT APPLE)
target_link_libraries(${PROJECT_NAME} PRIVATE X11 sfml-system sfml-window sfml-graphics sfml-audio sfml-network locallibraries ${OPENGL_LIBRARIES} csv)
endif (UNIX AND NOT APPLE)

if (APPLE)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network locallibraries ${OPENGL_LIBRARIES} csv)
endif (APPLE)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

GroupSourcesByFolder(${PROJECT_NAME}) # Groups sources by folder
