
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

  CustomTm t1;
  CustomTm t2;

  if (strptime("2011-05-11", "%Y-%m-%d", static_cast<std::tm*>(&t1)) == NULL) {
    std::cout << "strptime() error\n";
    exit(1);
  }

  if (strptime("2021-07-31", "%Y-%m-%d", static_cast<std::tm*>(&t2)) == NULL) {
    std::cout << "strptime() error\n";
    exit(1);
  }

  if (t1 > t2) {
    std::cout << "t1 is bigger than t2\n";
  } else {
    std::cout << "t2 is bigger than t1\n";
  }

  try {
    BitcoinExchange("data.csv", ",");
  } catch (const std::exception& e) {
    std::cout << e.what();
    exit(1);
  }
}