#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const char* file_name, const char* del) {
  std::ifstream file_read("data.csv");
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
  std::string tmp1;
  std::string tmp2;
  CustomTm tmp_key;
  float tmp_value;
  std::stringstream str_to_float;
  std::size_t del_pos;
  std::size_t del_len = std::strlen(del);

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
  tmp1 = buf.substr(0, del_pos);
  tmp2 = buf.substr(del_pos + del_len);
  if (tmp1 != std::string("date") || tmp2 != std::string("exchange_rate")) {
    file_read.close();
    throw std::invalid_argument("Error: invalid format.");
  }

  while (getline(file_read, buf)) {
    if (buf.length() > 0) {
      del_pos = buf.find(del);
      if (del_pos != std::string::npos) {
        tmp1 = buf.substr(0, del_pos);
        tmp2 = buf.substr(del_pos + del_len);
        if (tmp1.length() != 0 && tmp2.length() != 0) {
          if (strptime(tmp1.c_str(), "%Y-%m-%d", &tmp_key) == NULL) {
            continue;
          }
          str_to_float.clear();
          str_to_float << tmp2;
          str_to_float >> tmp_value;
          if (str_to_float.fail()) {
            continue;
          }
          data.insert(std::make_pair(tmp_key, tmp_value));
        }
      }
    }
  }
  if (file_read.eof()) {
    // std::cout << "File " << file_name << " read done\n";
    file_read.close();
  } else if (file_read.fail()) {
    file_read.close();
    throw std::invalid_argument("Error: error while read file.");
  }

  if (data.size() == 0) {
    throw std::invalid_argument("Error: empty file.");
  }
}

BitcoinExchange::BitcoinExchange() { ; }

BitcoinExchange::~BitcoinExchange() { ; }

BitcoinExchange::BitcoinExchange(const BitcoinExchange& origin) {
  data = origin.data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& origin) {
  if (this != &origin) {
    data = origin.data;
  }
  return *this;
}

std::map<CustomTm, float>::iterator BitcoinExchange::begin(void) {
  return data.begin();
}

std::map<CustomTm, float>::iterator BitcoinExchange::end(void) {
  return data.end();
}

const std::map<CustomTm, float>& BitcoinExchange::get_data(void) const {
  return data;
}

std::map<CustomTm, float>::const_iterator
BitcoinExchange::find_closest_lower_date(const CustomTm& input) {
  std::map<CustomTm, float>::const_iterator tmp_it;

  tmp_it = data.lower_bound(input);
  if (tmp_it != data.begin()) {
    if (tmp_it->first == input) {
      return tmp_it;
    } else {
      tmp_it--;
      return tmp_it;
    }
  } else {
    return data.end();
  }
}