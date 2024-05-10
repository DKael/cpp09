#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "BitcoinExchange.hpp"

#define BUFFER_SIZE 256

class CustonException : public std::exception {
 private:
  char message[BUFFER_SIZE];

  // not use
  CustonException();

 public:
  CustonException(const char* exceptionMsg);
  const char* what() const throw();
  virtual ~CustonException();
};

class InvalidFormat : public CustonException {
 private:
 public:
  InvalidFormat();
  virtual ~InvalidFormat();
};

CustonException::CustonException(const char* exceptionMsg) {
  size_t msg_len;
  int idx;

  msg_len = strlen(exceptionMsg);
  if (msg_len < BUFFER_SIZE) {
    strcpy(message, exceptionMsg);
  } else {
    strncpy(message, exceptionMsg, msg_len);
  }
}

const char* CustonException::what() const throw() { return message; }

InvalidFormat::InvalidFormat() : CustonException("Invalid format!") { ; }

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage : " << argv[0] << " <file_name>\n";
  }

  std::map<std::tm, float> data;
  std::map<std::tm, float> input_db;

  std::ifstream file_read("data.csv");
  if (file_read.is_open() == false) {
    std::cerr << "Cannot open file!\n";
    exit(1);
  }

  file_read.seekg(0, std::ios::end);
  int file_size = file_read.tellg();
  if (file_size == 0) {
    std::cerr << "Empty file!\n";
    exit(1);
  } else {
    file_read.seekg(0, std::ios::beg);
  }

  std::string buf;
  std::string tmp1;
  std::string tmp2;
  std::tm tmp_key;
  float tmp_value;
  std::stringstream str_to_float;
  std::size_t del_pos;

  if (getline(file_read, buf)) {
    if (buf.length() > 0) {
      del_pos = buf.find(',');
      if (del_pos != std::string::npos) {
        tmp1 = buf.substr(0, del_pos);
        tmp2 = buf.substr(del_pos + 1);
        if (tmp1 != std::string("date") ||
            tmp2 != std::string("exchange_rate")) {
          std::cerr << "Invalid format!\n";
          exit(1);
        }
      }
    } else {
      std::cerr << "Empty file!\n";
      exit(1);
    }
  } else {
    std::cerr << "Cannot read file!\n";
    exit(1);
  }
  while (getline(file_read, buf)) {
    if (buf.length() > 0) {
      del_pos = buf.find(',');
      if (del_pos != std::string::npos) {
        tmp1 = buf.substr(0, del_pos);
        tmp2 = buf.substr(del_pos + 1);
        if (tmp1.length() != 0 && tmp2.length() != 0) {
          str_to_float << tmp2;
          str_to_float >> tmp_value;
          str_to_float.clear();
          strptime(tmp1.c_str(), "%Y-%m-%d", &tmp_key);
        }
      }
    }
  }
  file_read.close();
}