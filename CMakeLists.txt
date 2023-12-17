cmake_minimum_required(VERSION 3.21.0)
project(DynEngine
  VERSION 0.1.0
  DESCRIPTION "Dynamics Engine"
  HOMEPAGE_URL https://github.com/emanspeaks/DynEngine
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

## configure CMake module search paths that depend on the project
## proj src dir is location of this file
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(CompileCommands)
include(DefaultBuildType)
include(DefaultInstallPath)
include(ForceUnicode)
include(DefineWindows)
include(HideVSCodeVars)

include(utf8)
include(windarkmode)

add_subdirectory(lib)
add_subdirectory(exe)

set(DynEngine_BUILD_TESTS OFF CACHE BOOL "Build the unit tests")
if(DynEngine_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
