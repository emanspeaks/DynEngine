add_executable(dynengineexe WIN32)  # the WIN32 is needed for the compiler to recognize this is a GUI
# for VS, set the startup target (the one that starts in debugger by default)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT dynengineexe)

if(WIN32)
  target_link_libraries(dynengineexe windarkmode)
  target_link_libraries(dynengineexe utf8)
endif()

target_link_libraries(dynengineexe dynenginelib)

add_subdirectory(include)
add_subdirectory(src)
