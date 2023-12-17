target_include_directories(dynengineexe PUBLIC .)

configure_file(version.h.in version.h)
target_include_directories(dynengineexe PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_sources(dynengineexe PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/version.h)

target_sources(dynengineexe PUBLIC gui.h)

if (WIN32)
  target_sources(dynengineexe PRIVATE winmain.h)
  target_sources(dynengineexe PRIVATE basewindow.h)
  target_sources(dynengineexe PRIVATE mainwindow.h)
endif()
