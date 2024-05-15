#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <sys/time.h>

#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

#define S_TO_US 1000000

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
  std::deque<int>::iterator origin_deq_head;
  std::deque<int> buf_deq;
  std::deque<int>::iterator buf_deq_head;
  std::deque<int> buf_deq1;
  std::deque<int>::iterator buf_deq1_head;

  timeval start_vec;
  timeval start_deq;
  timeval end_vec;
  timeval end_deq;

  void _merge_insertion_vec(int level, int item_cnt);
  void _merge_insertion_deq(int level, int item_cnt);

  // not use
  PmergeMe(void);
  PmergeMe(const PmergeMe& origin);
  PmergeMe& operator=(const PmergeMe& origin);

 public:
  static void PmergeMe_init(void);
  PmergeMe(const int argc, const char** argv);
  ~PmergeMe();

  void merge_insertion_sort(void);
  void print_vec(void) const;
  void print_deq(void) const;
  void print_vec_time(void) const;
  void print_deq_time(void) const;
};

long binary_insertion_vec(int target, const std::vector<int>& bs);
long binary_insertion_deq(int target, const std::deque<int>& bs);
inline long time_calc(timeval t1, timeval t2);
#endif