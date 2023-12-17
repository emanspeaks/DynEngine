include(FetchContent)

# set(utf8_tmp_cxx_std ${CMAKE_CXX_STANDARD})
# set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
  utf8
  GIT_REPOSITORY "https://github.com/emanspeaks/utf8.git"
  GIT_TAG cmake-fixes
)
FetchContent_MakeAvailable(utf8)
# include_directories(${utf8_SOURCE_DIR}/include)

# set(CMAKE_CXX_STANDARD ${utf8_tmp_cxx_std})
