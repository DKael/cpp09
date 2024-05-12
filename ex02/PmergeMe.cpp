#include "PmergeMe.hpp"

void PmergeMe::PmergeMe_init(void) {
  static bool init_flag = false;
  if (init_flag == false) {
    init_flag = true;
  }
}

PmergeMe::PmergeMe(const int argc, const char** argv) {
  std::stringstream str_to_num;
  int tmp_int;
  for (int i = 0; i < argc; i++) {
    str_to_num.clear();
    str_to_num << argv[i];
    str_to_num >> tmp_int;
    if (str_to_num.fail()) {
      throw std::invalid_argument("Error: can't convert to int.");
    }
    cont_vec.push_back(tmp_int);
    cont_deq.push_back(tmp_int);
  }
}

PmergeMe::~PmergeMe() { ; }

void PmergeMe::merge_insertion_sort(void) {}

void PmergeMe::print(void) const {
  std::vector<int>::const_iterator vec_head = cont_vec.begin();
  std::vector<int>::const_iterator vec_tail = cont_vec.end();
  std::deque<int>::const_iterator deq_head = cont_deq.begin();
  std::deque<int>::const_iterator deq_tail = cont_deq.end();

  for (; vec_head != vec_tail; ++vec_head) {
    std::cout << *vec_head << ' ';
  }
  std::cout << '\n';
  for (; deq_head != deq_tail; ++deq_head) {
    std::cout << *deq_head << ' ';
  }
  std::cout << '\n';
}
