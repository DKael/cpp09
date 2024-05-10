
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "BitcoinExchange.hpp"
#include "CustomTm.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage : " << argv[0] << " <file_name>\n";
    exit(1);
  }

  try {
    BitcoinExchange("data.csv", ",");
  } catch (const std::exception& e) {
    std::cout << e.what();
    exit(1);
  }
}