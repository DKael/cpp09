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
    BitcoinExchange btc("data.csv", ",");

    std::ifstream file_read(argv[1]);
    if (file_read.is_open() == false) {
      throw std::invalid_argument("Error: cannot open file.");
    }

    file_read.seekg(0, std::ios::end);
    int file_size = file_read.tellg();
    if (file_size == 0) {
      file_read.close();
      throw std::invalid_argument("Error: empty file.");
    }
    file_read.seekg(0, std::ios::beg);

    std::string buf;
    std::string date_str;
    std::string value_str;
    CustomTm date_tm;
    float value_float;
    std::size_t del_pos;
    std::string del(" | ");
    std::size_t del_len = del.length();

    if (!getline(file_read, buf)) {
      file_read.close();
      throw std::invalid_argument("Error: cannot read file.");
    }
    if (buf.length() == 0) {
      file_read.close();
      throw std::invalid_argument("Error: empty field value.");
    }
    del_pos = buf.find(del);
    if (del_pos == std::string::npos) {
      file_read.close();
      throw std::invalid_argument("Error: invalid format.");
    }
    date_str = buf.substr(0, del_pos);
    value_str = buf.substr(del_pos + del_len);
    if (date_str != std::string("date") || value_str != std::string("value")) {
      file_read.close();
      throw std::invalid_argument("Error: invalid format.");
    }

    while (getline(file_read, buf)) {
      std::stringstream str_to_float;

      if (buf.length() == 0) {
        std::cout << "Error: Empty line.\n";
        continue;
      }
      del_pos = buf.find(del);
      if (del_pos == std::string::npos) {
        std::cout << "Error: Invalid format.\n";
        continue;
      }
      date_str = buf.substr(0, del_pos);
      value_str = buf.substr(del_pos + del_len);
      if (date_str.length() == 0 || value_str.length() == 0) {
        std::cout << "Error: Invalid format.\n";
        continue;
      }
      if (strptime(date_str.c_str(), "%Y-%m-%d", &date_tm) == NULL) {
        std::cout << "Error: bad input => " << date_str << '\n';
        continue;
      }
      str_to_float << value_str;
      str_to_float >> value_float;
      if (str_to_float.fail()) {
        std::cout << "Error: bad input => " << value_str
                  << ", can't convert to float\n";
        continue;
      }
      if (value_float < 0) {
        std::cout << "Error: not a positive number.\n";
        continue;
      }
      if (value_float > 1000) {
        std::cout << "Error: too large number.\n";
        continue;
      }
      std::map<CustomTm, float>::const_iterator it =
          btc.find_closest_lower_date(date_tm);

      if (it == btc.end()) {
        std::cout << "Error: Data not exist.\n";
        continue;
      }

      std::cout << date_str << " => " << value_str << " = "
                << value_float * it->second << '\n';
    }
    if (file_read.eof()) {
      file_read.close();
    } else if (file_read.fail()) {
      file_read.close();
      throw std::invalid_argument("Error while read file!");
    }

  } catch (const std::exception& e) {
    std::cout << e.what() << '\n';
    exit(1);
  }
}
