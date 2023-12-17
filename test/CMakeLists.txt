add_executable(dynenginetest)

target_link_libraries(dynenginetest dynenginelib)

add_subdirectory(include)
add_subdirectory(src)

# for VS, set the startup target (the one that starts in debugger by default)
# set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT dynenginetest)

add_test(NAME DynEngineTests COMMAND dynenginetest)
