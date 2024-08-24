cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+

project(minimal CXX)

set(CMAKE_CXX_STANDARD 20) # Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.0.1 # You can specify the version you need
)
FetchContent_MakeAvailable(catch2)

# Engine library
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/engine/src/*.cpp")
set(ENGINE_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/engine/include/")
add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC ${ENGINE_INCLUDE})
target_link_libraries(engine PUBLIC raylib)

# Tests
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/test/*.cpp")
add_executable(test ${TEST_SOURCES})
target_link_libraries(test PRIVATE engine Catch2::Catch2WithMain)

# Runtime test
file(GLOB_RECURSE RUNTIME_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/runtime-test/src/*.cpp")
set(RUNTIME_TEST_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/runtime-test/include/")
add_executable(runtime_test ${RUNTIME_TEST_SOURCES})
target_include_directories(runtime_test PRIVATE ${RUNTIME_TEST_INCLUDE})
target_link_libraries(runtime_test PRIVATE engine)

add_custom_command(
    TARGET runtime_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_LIST_DIR}/runtime-test/assets"
    "$<TARGET_FILE_DIR:runtime_test>/assets"
)

# Setting ASSETS_PATH
target_compile_definitions(runtime_test PUBLIC ASSETS_PATH="../runtime-test/assets")

# Debug options
option(ENABLE_DEBUG "Enable debug options" OFF)
if (ENABLE_DEBUG)
  target_compile_definitions(runtime_test PUBLIC DEBUG_OPTIONS)
endif()
