#include "CustomTm.hpp"

CustomTm::CustomTm() { ; }

CustomTm::~CustomTm() { ; }

CustomTm::CustomTm(const CustomTm& origin) {
  this->tm_sec = origin.tm_sec;		
	this->tm_min = origin.tm_min;		
	this->tm_hour = origin.tm_hour;	
	this->tm_mday = origin.tm_mday;	
	this->tm_mon = origin.tm_mon;		
	this->tm_year = origin.tm_year;	
	this->tm_wday = origin.tm_wday;	
	this->tm_yday = origin.tm_yday;
	this->tm_isdst = origin.tm_isdst;
  this->tm_gmtoff = origin.tm_gmtoff;
  this->tm_zone = origin.tm_zone;
}

CustomTm& CustomTm::operator=(const CustomTm& origin) {
  if (this != &origin) {
    this->tm_sec = origin.tm_sec;		
    this->tm_min = origin.tm_min;		
    this->tm_hour = origin.tm_hour;	
    this->tm_mday = origin.tm_mday;	
    this->tm_mon = origin.tm_mon;		
    this->tm_year = origin.tm_year;	
    this->tm_wday = origin.tm_wday;	
    this->tm_yday = origin.tm_yday;	
    this->tm_isdst = origin.tm_isdst;
    this->tm_gmtoff = origin.tm_gmtoff;
    this->tm_zone = origin.tm_zone;
  }
  return *this;
}

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
  out << (obj.tm_year + 1900) << '-' << (obj.tm_mon + 1) << '-' << obj.tm_mday;
  return out;
}