include(FetchContent)

FetchContent_Declare(
  utf8
  GIT_REPOSITORY "https://github.com/neacsum/utf8.git"
  # GIT_REPOSITORY "https://github.com/emanspeaks/utf8.git"
  GIT_TAG main
)
FetchContent_MakeAvailable(utf8)
