#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "CustomTm.hpp"

class BitcoinExchange {
 private:
  std::map<CustomTm, float> data;

 public:
  BitcoinExchange(const char* file_name, const std::string del);
  BitcoinExchange();
  ~BitcoinExchange();
  BitcoinExchange(const BitcoinExchange& origin);
  BitcoinExchange& operator=(const BitcoinExchange& origin);

  std::map<CustomTm, float>::iterator begin(void);
  std::map<CustomTm, float>::iterator end(void);
  const std::map<CustomTm, float>& get_data(void) const;
  std::map<CustomTm, float>::const_iterator find_closest_lower_date(
      const CustomTm& input);
};

#endif