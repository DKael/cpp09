#ifndef CUMTOMTM_HPP
#define CUMTOMTM_HPP

#include <ctime>

class CustomTm : public std::tm {
 private:
 public:
  bool operator>(CustomTm& comp);
  bool operator>=(CustomTm& comp);
  bool operator<(CustomTm& comp);
  bool operator<=(CustomTm& comp);
  bool operator==(CustomTm& comp);
  bool operator!=(CustomTm& comp);
};

#endif