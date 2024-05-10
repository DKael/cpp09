#include "CustomTm.hpp"

bool CustomTm::operator>(const CustomTm& comp) const {
  if (this->tm_year > comp.tm_year) {
    return true;
  } else if (this->tm_year < comp.tm_year) {
    return false;
  }

  if (this->tm_mon > comp.tm_mon) {
    return true;
  } else if (this->tm_mon < comp.tm_mon) {
    return false;
  }

  if (this->tm_mday > comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator>=(const CustomTm& comp) const {
  if (this->tm_year > comp.tm_year) {
    return true;
  } else if (this->tm_year < comp.tm_year) {
    return false;
  }

  if (this->tm_mon > comp.tm_mon) {
    return true;
  } else if (this->tm_mon < comp.tm_mon) {
    return false;
  }

  if (this->tm_mday >= comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}
bool CustomTm::operator<(const CustomTm& comp) const {
  if (this->tm_year < comp.tm_year) {
    return true;
  } else if (this->tm_year > comp.tm_year) {
    return false;
  }

  if (this->tm_mon < comp.tm_mon) {
    return true;
  } else if (this->tm_mon > comp.tm_mon) {
    return false;
  }

  if (this->tm_mday < comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator<=(const CustomTm& comp) const {
  if (this->tm_year < comp.tm_year) {
    return true;
  } else if (this->tm_year > comp.tm_year) {
    return false;
  }

  if (this->tm_mon < comp.tm_mon) {
    return true;
  } else if (this->tm_mon > comp.tm_mon) {
    return false;
  }

  if (this->tm_mday <= comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator==(const CustomTm& comp) const {
  if (this->tm_year == comp.tm_year && this->tm_mon == comp.tm_mon &&
      this->tm_mday == comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator!=(const CustomTm& comp) const {
  if (this->tm_year != comp.tm_year || this->tm_mon != comp.tm_mon ||
      this->tm_mday != comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

std::ostream& operator<<(std::ostream& out, const CustomTm& obj) {
  out << (obj.tm_year + 1900) << '-' << (obj.tm_mon + 1) << '-' << obj.tm_mday ;
  return out;
}