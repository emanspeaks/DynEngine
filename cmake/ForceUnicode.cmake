## Force Unicode always
add_compile_definitions(_UNICODE UNICODE)
if(MSVC)
  add_compile_options(/utf-8)
endif()

# https://wg21.link/p2513
if(MSVC)
  add_compile_options(/Zc:char8_t-)
else()
  add_compile_options(-fno-char8_t)
endif()
