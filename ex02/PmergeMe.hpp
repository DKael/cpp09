#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <ctime>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

class PmergeMe {
 private:
  static std::vector<std::uint64_t> jacobsthal_num;

  std::vector<int> origin_vec;
  std::vector<int>::iterator origin_vec_head;
  std::vector<int> buf_vec;
  std::vector<int>::iterator buf_vec_head;
  std::vector<int> buf_vec1;
  std::vector<int>::iterator buf_vec1_head;

  std::deque<int> origin_deq;

  std::time_t start1;
  std::time_t start2;
  std::time_t end1;
  std::time_t end2;

  void _merge_insertion_vec(int level, int item_cnt);

  // not use
  PmergeMe(void);
  PmergeMe(const PmergeMe& origin);
  PmergeMe& operator=(const PmergeMe& origin);

 public:
  static void PmergeMe_init(void);
  PmergeMe(const int argc, const char** argv);
  ~PmergeMe();

  void merge_insertion_sort(void);
  void print(void) const;
};

long binary_insertion_vec(int target, const std::vector<int>& bs);

#endif