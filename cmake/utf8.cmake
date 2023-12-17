include(FetchContent)

FetchContent_Declare(
  utf8
  GIT_REPOSITORY "https://github.com/emanspeaks/utf8.git"
  GIT_TAG cmake-fixes
)
FetchContent_MakeAvailable(utf8)
