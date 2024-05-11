#include "CustomTm.hpp"

CustomTm::CustomTm() {
  tm_sec = 0;
  tm_min = 0;
  tm_hour = 0;
  tm_mday = 0;
  tm_mon = 0;
  tm_year = 0;
  tm_wday = 0;
  tm_yday = 0;
  tm_isdst = 0;
  tm_gmtoff = 0;
  tm_zone = 0;
}

CustomTm::~CustomTm() { ; }

CustomTm::CustomTm(const CustomTm& origin) {
  tm_sec = origin.tm_sec;
  tm_min = origin.tm_min;
  tm_hour = origin.tm_hour;
  tm_mday = origin.tm_mday;
  tm_mon = origin.tm_mon;
  tm_year = origin.tm_year;
  tm_wday = origin.tm_wday;
  tm_yday = origin.tm_yday;
  tm_isdst = origin.tm_isdst;
  tm_gmtoff = origin.tm_gmtoff;
  tm_zone = origin.tm_zone;
}

CustomTm& CustomTm::operator=(const CustomTm& origin) {
  if (this != &origin) {
    tm_sec = origin.tm_sec;
    tm_min = origin.tm_min;
    tm_hour = origin.tm_hour;
    tm_mday = origin.tm_mday;
    tm_mon = origin.tm_mon;
    tm_year = origin.tm_year;
    tm_wday = origin.tm_wday;
    tm_yday = origin.tm_yday;
    tm_isdst = origin.tm_isdst;
    tm_gmtoff = origin.tm_gmtoff;
    tm_zone = origin.tm_zone;
  }
  return *this;
}

bool CustomTm::chk_valid(void) {
  if (tm_mon == 3 || tm_mon == 5 || tm_mon == 8 || tm_mon == 10) {
    if (tm_mday > 30 || tm_mday < 1) {
      return false;
    } else {
      return true;
    }
  } else if (tm_mon == 1) {
    int leap_year_offset =
        (((tm_year % 4 == 0) && (tm_year % 100 != 0)) || (tm_year % 400 == 0))
            ? 1
            : 0;
    if (tm_mday > 28 + leap_year_offset || tm_mday < 1) {
      return false;
    } else {
      return true;
    }
  } else {
    if (tm_mday > 31 || tm_mday < 1) {
      return false;
    } else {
      return true;
    }
  }
}

bool CustomTm::operator>(const CustomTm& comp) const {
  if (tm_year > comp.tm_year) {
    return true;
  } else if (tm_year < comp.tm_year) {
    return false;
  }

  if (tm_mon > comp.tm_mon) {
    return true;
  } else if (tm_mon < comp.tm_mon) {
    return false;
  }

  if (tm_mday > comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator>=(const CustomTm& comp) const {
  if (tm_year > comp.tm_year) {
    return true;
  } else if (tm_year < comp.tm_year) {
    return false;
  }

  if (tm_mon > comp.tm_mon) {
    return true;
  } else if (tm_mon < comp.tm_mon) {
    return false;
  }

  if (tm_mday >= comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}
bool CustomTm::operator<(const CustomTm& comp) const {
  if (tm_year < comp.tm_year) {
    return true;
  } else if (tm_year > comp.tm_year) {
    return false;
  }

  if (tm_mon < comp.tm_mon) {
    return true;
  } else if (tm_mon > comp.tm_mon) {
    return false;
  }

  if (tm_mday < comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator<=(const CustomTm& comp) const {
  if (tm_year < comp.tm_year) {
    return true;
  } else if (tm_year > comp.tm_year) {
    return false;
  }

  if (tm_mon < comp.tm_mon) {
    return true;
  } else if (tm_mon > comp.tm_mon) {
    return false;
  }

  if (tm_mday <= comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator==(const CustomTm& comp) const {
  if (tm_year == comp.tm_year && tm_mon == comp.tm_mon &&
      tm_mday == comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

bool CustomTm::operator!=(const CustomTm& comp) const {
  if (tm_year != comp.tm_year || tm_mon != comp.tm_mon ||
      tm_mday != comp.tm_mday) {
    return true;
  } else {
    return false;
  }
}

std::ostream& operator<<(std::ostream& out, const CustomTm& obj) {
  out << (obj.tm_year + 1900) << '-' << (obj.tm_mon + 1) << '-' << obj.tm_mday;
  return out;
}