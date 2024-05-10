#include "CustomTm.hpp"

bool CustomTm::operator>(CustomTm& comp) {
  std::time_t tmp1 = mktime(static_cast<std::tm*>(this));
  std::time_t tmp2 = mktime(static_cast<std::tm*>(&comp));

  if (tmp1 > tmp2) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator>=(CustomTm& comp) {
  if (mktime(this) >= mktime(&comp)) {
    return true;
  } else {
    return false;
  }
}
bool CustomTm::operator<(CustomTm& comp) {
  if (mktime(this) < mktime(&comp)) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator<=(CustomTm& comp) {
  if (mktime(this) <= mktime(&comp)) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator==(CustomTm& comp) {
  if (mktime(this) == mktime(&comp)) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator!=(CustomTm& comp) {
  if (mktime(this) != mktime(&comp)) {
    return true;
  } else {
    return false;
  }
}