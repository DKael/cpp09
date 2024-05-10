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
  BitcoinExchange(const char* file_name, const char* del);
  BitcoinExchange();
  ~BitcoinExchange();
  BitcoinExchange(const BitcoinExchange& origin);
  BitcoinExchange& operator=(const BitcoinExchange& origin);
};

#endif