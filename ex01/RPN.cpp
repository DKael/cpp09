#include "RPN.hpp"

std::string ft_strip(const std::string& origin) {
  std::size_t front_pos;
  std::size_t back_pos;

  front_pos = origin.find_first_not_of(" \n\t\v\f\r");
  back_pos = origin.find_last_not_of(" \n\t\v\f\r");
  if (front_pos == std::string::npos || back_pos == std::string::npos) {
    return "";
  }
  return origin.substr(front_pos, back_pos - front_pos + 1);
}