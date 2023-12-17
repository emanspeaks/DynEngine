target_sources(dynengineexe PRIVATE gui.cpp)

if (WIN32)
  target_sources(dynengineexe PRIVATE winmain.cpp)
  target_sources(dynengineexe PRIVATE mainwindow.cpp)
endif()
