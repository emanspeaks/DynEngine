target_sources(dynengineexe PRIVATE gui.cpp)
if (WIN32)
  target_sources(dynengineexe PRIVATE windows_gui.cpp)
  target_sources(dynengineexe PRIVATE windows_strings.cpp)
endif()
