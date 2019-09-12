#include "dynenginelib.h"

std::string get_window_message()
{
  const std::string msg("Hello, World, from the library!");
  std::string out;
  return out.assign(msg);
}
