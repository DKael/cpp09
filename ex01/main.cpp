#include "RPN.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage : " << argv[0]
              << " <inverted Polish mathematical expression>\n";
    exit(1);
  }

  try {
    std::string exp(argv[1]);
    std::stack<int> number_box;

    if (exp.find_first_not_of(" 0123456789+-*/") != std::string::npos) {
      throw std::invalid_argument("Error: invalid expression.");
    }

    exp = ft_strip(exp);
    if (exp.length() == 0) {
      throw std::invalid_argument("Error: empty expression.");
    }

    std::stringstream split(exp);
    std::stringstream str_to_num;
    std::string tmp;
    int num1 = 0;
    int num2 = 0;
    int result = 0;

    while (split >> tmp) {
      if (tmp.find_first_not_of("+-*/") == std::string::npos) {
        if (tmp.length() != 1) {
          throw std::invalid_argument("Error: invalid operator.");
        }
        if (number_box.size() <= 1) {
          throw std::invalid_argument("Error: short of operands.");
        }
        num2 = number_box.top();
        number_box.pop();
        num1 = number_box.top();
        number_box.pop();
        if (tmp == std::string("+")) {
          result = num1 + num2;
        } else if (tmp == std::string("-")) {
          result = num1 - num2;
        } else if (tmp == std::string("*")) {
          result = num1 * num2;
        } else if (tmp == std::string("/")) {
          if (num2 == 0) {
            throw std::logic_error("Error: divide by 0.");
          }
          result = num1 / num2;
        } else {
          throw std::invalid_argument("Error: unknown error.");
        }
        number_box.push(result);
      } else {
        str_to_num.clear();
        str_to_num << tmp;
        str_to_num >> result;
        if (str_to_num.fail()) {
          throw std::invalid_argument(
              "Error: can't convert number expression to int.");
        }
        number_box.push(result);
      }
    }
    if (number_box.size() != 1) {
      throw std::invalid_argument("Error: incomplete operation.");
    }
    result = number_box.top();
    number_box.pop();
    std::cout << result << '\n';

  } catch (const std::exception& e) {
    std::cout << e.what() << '\n';
    exit(1);
  }
}