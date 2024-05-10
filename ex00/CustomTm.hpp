#ifndef CUMTOMTM_HPP
#define CUMTOMTM_HPP

#include <ctime>
#include <ostream>

class CustomTm : public std::tm {
 private:
 public:
  bool operator>(const CustomTm& comp) const;
  bool operator>=(const CustomTm& comp) const;
  bool operator<(const CustomTm& comp) const;
  bool operator<=(const CustomTm& comp) const;
  bool operator==(const CustomTm& comp) const;
  bool operator!=(const CustomTm& comp) const;
};

std::ostream& operator<<(std::ostream& out, const CustomTm& obj);

#endif