cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)

# ---- Project ----

# Note: update this to your new project's name and version
project(
  AlienInvadersRetro
  VERSION 1.0
  LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

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

# GLAD
CPMAddPackage(
  NAME glad
  GITHUB_REPOSITORY Dav1dde/glad
  VERSION 0.1.33
)

# GLM
CPMAddPackage(
  NAME glm
  GITHUB_REPOSITORY g-truc/glm
  GIT_TAG 0.9.9.7
)

# BOOST/ASIO
CPMAddPackage(
  NAME asio
  GITHUB_REPOSITORY boostorg/asio
  GIT_TAG boost-1.80.0
  OPTIONS "ASIO_BUILD_EXAMPLES NO" "ASIO_BUILD_TESTS NO" "ASIO_ENABLE_INSTALL YES"
)


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

# Some platforms need OpenGL. Most don't, because we are using the gl3w loader library.
find_package(OpenGL REQUIRED)


CPMAddPackage(
  NAME sfml
  GITHUB_REPOSITORY SFML/SFML
  GIT_TAG 2.5.x
)
set_target_properties(sfml-system PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-network PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-graphics PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-window PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-audio PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)


# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(alieninvaderslibrary INTERFACE)
add_library(alieninvaderslibrary ${headers} ${sources})

set_target_properties(alieninvaderslibrary PROPERTIES CXX_STANDARD 17)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(alieninvaderslibrary PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
if (WIN32)
find_package(SFML REQUIRED COMPONENTS graphics window system audio network)
target_link_libraries(alieninvaderslibrary PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network boost_system)
endif (WIN32)


if (UNIX AND NOT APPLE)
target_link_libraries(alieninvaderslibrary PRIVATE X11 sfml-system sfml-window sfml-graphics sfml-audio sfml-network boost_system)
endif (UNIX AND NOT APPLE)

if (APPLE)
target_link_libraries(alieninvaderslibrary PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network boost_system)
endif (APPLE)


target_include_directories(
  alieninvaderslibrary PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/alieninvaderslibrary-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER alieninvaderslibrary/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME alieninvaderslibrary
  VERSION ${PROJECT_VERSION}
  NAMESPACE alieninvaderslibrary
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/alieninvaderslibrary-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
  DEPENDENCIES "sfml 2.5.x"
)
