cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
# set(CMAKE_CXX_STANDARD 17)

project(StandaloneProject LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

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

# GLFW
CPMFindPackage(
    NAME glfw3
    # GITHUB_REPOSITORY glfw/glfw
    # GIT_TAG 3.3.2
    URL https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip
    URL_HASH SHA256=08a33a512f29d7dbf78eab39bd7858576adcc95228c9efe8e4bc5f0f3261efc7
    VERSION 3.2
    OPTIONS
        "ENKITS_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_TESTS ON"
        "GLFW_BUILD_DOCS ON"
        "GLFW_BUILD_INSTALL ON"
)


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


CPMAddPackage(NAME AlienInvadersRetro SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui_sfml/*.cpp)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/../imgui/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/../imgui_sfml/*.h")

add_executable(${PROJECT_NAME} ${sources} ${headers})


set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "AlienInvadersRetro")

if (WIN32)
find_package(SFML REQUIRED COMPONENTS graphics window system audio network)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network opengl32
  winmm gdi32
)
endif (WIN32)

if (UNIX)
target_link_libraries(${PROJECT_NAME} PRIVATE X11 sfml-system sfml-window sfml-graphics sfml-audio sfml-network glfw)
endif (UNIX)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

GroupSourcesByFolder(${PROJECT_NAME}) # Groups sources by folder
