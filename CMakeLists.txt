cmake_minimum_required(VERSION 3.15.3)

## define the project
project(DynEngine
        VERSION 0.1.0.0
        DESCRIPTION "Dynamics Engine"
        HOMEPAGE_URL https://github.com/emanspeaks/DynEngine
        LANGUAGES CXX)

################################################################################
## Configure CMake project paths
################################################################################

## configure CMake module search paths that depend on the project
## proj src dir is location of this file
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# list(APPEND CMAKE_MODULE_PATH ${PROJECT_BINARY_DIR})

## path for *.mod files
## proj build dir is set by CMake user (usually build/)
# set(CMAKE_Fortran_MODULE_DIRECTORY ${PROJECT_BINARY_DIR}/mod)

## define the project default install path, if necessary
##
## CMake's native defaults are:
## Windows: C:\\Program Files
## Else: /usr/local
##
## The lines below default to using this file's directory as install root
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR} CACHE PATH "Choose the installation directory" FORCE)
  ## In case this build includes multiple projects,
  ## only set for the first (in theory, topmost) project
  unset(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif()

## Set the project default build type
include(DefaultBuildType)

## Hides stuff added by VSCode CMake Tools
mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
mark_as_advanced(CMAKE_GNUtoMS)
mark_as_advanced(CMAKE_C_COMPILER)

################################################################################
## Define project contents
################################################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE CACHE BOOL "Generate compile_commands.json" FORCE)
mark_as_advanced(CMAKE_EXPORT_COMPILE_COMMANDS)
## VS Code bug workaround: see https://github.com/microsoft/vscode-cpptools/issues/1718#issuecomment-410515196
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF CACHE BOOL "Disable use of @CMakeFiles syntax in compile_commands.json" FORCE)
mark_as_advanced(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES)


## Force Unicode always
add_compile_definitions(_UNICODE UNICODE)

add_library(dynenginelib STATIC)

add_executable(dynengineexe WIN32)
target_link_libraries(dynengineexe dynenginelib)
set_target_properties(dynengineexe PROPERTIES COMPILE_DEFINITIONS "WIN32;_WINDOWS")

## Add the subproject subdirectories
add_subdirectory(include/lib)
add_subdirectory(src/lib)
add_subdirectory(include/exe)
add_subdirectory(src/exe)

## for VS, set the startup target (the one that starts in debugger by default)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT dynengineexe)

## If we had unit tests, we could define them here like below
set(DynEngine_BUILD_TESTS OFF CACHE BOOL "Build the unit tests")
if(DynEngine_BUILD_TESTS)
  enable_testing()

  ## configure the test and its dependencies here like any other target
  add_executable(dynenginetest)
  add_subdirectory(src/test)
  target_link_libraries(dynenginetest dynenginelib)

  ## add the test target to the project
  add_test(NAME DynEngineTests COMMAND dynenginetest)
endif()
