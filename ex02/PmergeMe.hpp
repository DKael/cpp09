#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <ctime>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

class PmergeMe {
 private:
  std::list<int> cont_lst;
  std::vector<int> cont_vec;
  std::time_t start1;
  std::time_t start2;
  std::time_t end1;
  std::time_t end2;

  // not use
  PmergeMe(void);
  PmergeMe(const PmergeMe& origin);
  PmergeMe& operator=(const PmergeMe& origin);

 public:
  PmergeMe(const int argc, const char** argv);
  ~PmergeMe();

  void merge_insertion_sort(void);
  void print(void);
};

#endif