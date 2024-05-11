#include "PmergeMe.hpp"

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
    cont_lst.push_back(tmp_int);
    cont_vec.push_back(tmp_int);
  }
}

PmergeMe::~PmergeMe() { ; }

void PmergeMe::merge_insertion_sort(void) {}

template <typename Cont>
void merge_sort(Cont input) {}

void PmergeMe::print(void) {
  std::vector<int>::iterator vec_head = cont_vec.begin();
  std::vector<int>::iterator vec_tail = cont_vec.end();
  std::list<int>::iterator lst_head = cont_lst.begin();
  std::list<int>::iterator lst_tail = cont_lst.end();

  for (; vec_head != vec_tail; ++vec_head) {
    std::cout << *vec_head << ' ';
  }
  std::cout << '\n';
  for (; lst_head != lst_tail; ++lst_head) {
    std::cout << *lst_head << ' ';
  }
  std::cout << '\n';
}