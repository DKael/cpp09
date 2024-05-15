#include "PmergeMe.hpp"

std::vector<std::uint64_t> PmergeMe::jacobsthal_num;

void PmergeMe::PmergeMe_init(void) {
  static bool init_flag = false;
  if (init_flag == false) {
    init_flag = true;
    jacobsthal_num.push_back(0);
    jacobsthal_num.push_back(1);
    for (int i = 1; i < 40; i++) {
      jacobsthal_num.push_back((1ULL << i) - jacobsthal_num[i]);
    }
  }
}

PmergeMe::PmergeMe(const int argc, const char** argv) {
  std::stringstream str_to_num;
  int tmp_int;

  origin_vec.reserve(argc);
  buf_vec.reserve(argc);
  buf_vec1.reserve(argc);
  for (int i = 0; i < argc; i++) {
    str_to_num.clear();
    str_to_num << argv[i];
    str_to_num >> tmp_int;
    if (str_to_num.fail()) {
      throw std::invalid_argument("Error: can't convert to int.");
    }
    if (tmp_int < 0) {
      throw std::invalid_argument("Error: negative number included.");
    }
    origin_vec.push_back(tmp_int);
    buf_vec.push_back(tmp_int);
    buf_vec1.push_back(0);

    origin_deq.push_back(tmp_int);
    buf_deq.push_back(tmp_int);
    buf_deq1.push_back(0);
  }
  origin_vec_head = origin_vec.begin();
  buf_vec_head = buf_vec.begin();
  buf_vec1_head = buf_vec1.begin();

  origin_deq_head = origin_deq.begin();
  buf_deq_head = buf_deq.begin();
  buf_deq1_head = buf_deq1.begin();
}

PmergeMe::~PmergeMe() { ; }

void PmergeMe::merge_insertion_sort(void) {
  gettimeofday(&start_vec, NULL);
  if (origin_vec.size() < 2) {
    return;
  }
  _merge_insertion_vec(0, origin_vec.size());
  gettimeofday(&end_vec, NULL);

  gettimeofday(&start_deq, NULL);
  if (origin_deq.size() < 2) {
    return;
  }
  _merge_insertion_deq(0, origin_deq.size());
  gettimeofday(&end_deq, NULL);
}

void PmergeMe::_merge_insertion_vec(int level, int item_num) {
  int item_size = (1 << level);
  int pair_size = (item_size << 1);
  int pair_num = (item_num / 2);
  int is_size_odd = (item_num % 2);
  int idx = 0;

  std::vector<int>::iterator copy_start_loc;

  for (int i = 0; i < pair_num; i++) {
    idx = i * pair_size;
    if (origin_vec[idx] < origin_vec[idx + item_size]) {
      copy_start_loc = origin_vec_head + idx + item_size;
      std::copy(copy_start_loc, copy_start_loc + item_size, buf_vec_head + idx);
      copy_start_loc = origin_vec_head + idx;
      std::copy(copy_start_loc, copy_start_loc + item_size,
                buf_vec_head + idx + item_size);
    }
  }
  std::copy(buf_vec_head, buf_vec_head + pair_num * pair_size, origin_vec_head);

  if (pair_num != 1) {
    _merge_insertion_vec(level + 1, pair_num);
  }

  std::copy(origin_vec_head + item_size, origin_vec_head + pair_size,
            buf_vec_head);
  std::copy(origin_vec_head, origin_vec_head + item_size,
            buf_vec_head + item_size);
  int a_cnt = 2;
  for (int i = 1; i < pair_num; i++) {
    copy_start_loc = origin_vec_head + (i * pair_size);
    std::copy(copy_start_loc, copy_start_loc + item_size,
              buf_vec_head + ((i + 1) * item_size));
    a_cnt++;
    copy_start_loc = copy_start_loc + item_size;
    std::copy(copy_start_loc, copy_start_loc + item_size,
              buf_vec1.begin() + ((i - 1) * item_size));
  }

  int jacob_idx = 2;

  while (jacobsthal_num[jacob_idx] < pair_num + is_size_odd) {
    ++jacob_idx;
  }

  int i;
  for (i = 3; i < jacob_idx; i++) {
    for (std::uint64_t j = jacobsthal_num[i]; j > jacobsthal_num[i - 1]; j--) {
      copy_start_loc = buf_vec1_head + (j - 2) * item_size;
      int pair_Key = *copy_start_loc;
      std::vector<int> binary_search;
      for (int k = 0; k < jacobsthal_num[i] + jacobsthal_num[i - 1] - 1; k++) {
        binary_search.push_back(buf_vec[k * item_size]);
      }
      int insertion_idx = binary_insertion_vec(pair_Key, binary_search) + 1;
      for (int k = a_cnt * item_size - 1;
           k >= insertion_idx * static_cast<int>(item_size); --k) {
        buf_vec[k + item_size] = buf_vec[k];
      }
      std::copy(copy_start_loc, copy_start_loc + item_size,
                buf_vec_head + insertion_idx * item_size);
      a_cnt++;
    }
  }

  if (is_size_odd) {
    copy_start_loc = origin_vec_head + pair_num * pair_size;
    int pair_Key = *copy_start_loc;
    std::vector<int> binary_search;
    for (int k = 0; k < a_cnt; k++) {
      binary_search.push_back(buf_vec[k * item_size]);
    }
    int insertion_idx = binary_insertion_vec(pair_Key, binary_search) + 1;
    for (int k = a_cnt * item_size - 1;
         k >= insertion_idx * static_cast<int>(item_size); --k) {
      buf_vec[k + item_size] = buf_vec[k];
    }
    std::copy(copy_start_loc, copy_start_loc + item_size,
              buf_vec_head + insertion_idx * item_size);
    a_cnt++;
  }

  for (int j = pair_num; j > jacobsthal_num[i - 1]; j--) {
    copy_start_loc = buf_vec1_head + (j - 2) * item_size;
    int pair_Key = *copy_start_loc;
    std::vector<int> binary_search;
    for (int k = 0; k < jacobsthal_num[i - 1] + pair_num - 1 + is_size_odd;
         k++) {
      binary_search.push_back(buf_vec[k * item_size]);
    }
    int insertion_idx = binary_insertion_vec(pair_Key, binary_search) + 1;
    for (int k = a_cnt * item_size - 1;
         k >= insertion_idx * static_cast<int>(item_size); --k) {
      buf_vec[k + item_size] = buf_vec[k];
    }
    std::copy(copy_start_loc, copy_start_loc + item_size,
              buf_vec_head + insertion_idx * item_size);
    a_cnt++;
  }

  std::copy(buf_vec_head, buf_vec_head + item_num * item_size, origin_vec_head);
  return;
}

void PmergeMe::_merge_insertion_deq(int level, int item_num) {
  int item_size = (1 << level);
  int pair_size = (item_size << 1);
  int pair_num = (item_num / 2);
  int is_size_odd = (item_num % 2);
  int idx = 0;

  std::deque<int>::iterator copy_start_loc;

  for (int i = 0; i < pair_num; i++) {
    idx = i * pair_size;
    if (origin_deq[idx] < origin_deq[idx + item_size]) {
      copy_start_loc = origin_deq_head + idx + item_size;
      std::copy(copy_start_loc, copy_start_loc + item_size, buf_deq_head + idx);
      copy_start_loc = origin_deq_head + idx;
      std::copy(copy_start_loc, copy_start_loc + item_size,
                buf_deq_head + idx + item_size);
    }
  }
  std::copy(buf_deq_head, buf_deq_head + pair_num * pair_size, origin_deq_head);

  if (pair_num != 1) {
    _merge_insertion_deq(level + 1, pair_num);
  }

  std::copy(origin_deq_head + item_size, origin_deq_head + pair_size,
            buf_deq_head);
  std::copy(origin_deq_head, origin_deq_head + item_size,
            buf_deq_head + item_size);
  int a_cnt = 2;
  for (int i = 1; i < pair_num; i++) {
    copy_start_loc = origin_deq_head + (i * pair_size);
    std::copy(copy_start_loc, copy_start_loc + item_size,
              buf_deq_head + ((i + 1) * item_size));
    a_cnt++;
    copy_start_loc = copy_start_loc + item_size;
    std::copy(copy_start_loc, copy_start_loc + item_size,
              buf_deq1.begin() + ((i - 1) * item_size));
  }

  int jacob_idx = 2;

  while (jacobsthal_num[jacob_idx] < pair_num + is_size_odd) {
    ++jacob_idx;
  }

  int i;
  for (i = 3; i < jacob_idx; i++) {
    for (std::uint64_t j = jacobsthal_num[i]; j > jacobsthal_num[i - 1]; j--) {
      copy_start_loc = buf_deq1_head + (j - 2) * item_size;
      int pair_Key = *copy_start_loc;
      std::deque<int> binary_search;
      for (int k = 0; k < jacobsthal_num[i] + jacobsthal_num[i - 1] - 1; k++) {
        binary_search.push_back(buf_deq[k * item_size]);
      }
      int insertion_idx = binary_insertion_deq(pair_Key, binary_search) + 1;
      for (int k = a_cnt * item_size - 1;
           k >= insertion_idx * static_cast<int>(item_size); --k) {
        buf_deq[k + item_size] = buf_deq[k];
      }
      std::copy(copy_start_loc, copy_start_loc + item_size,
                buf_deq_head + insertion_idx * item_size);
      a_cnt++;
    }
  }

  if (is_size_odd) {
    copy_start_loc = origin_deq_head + pair_num * pair_size;
    int pair_Key = *copy_start_loc;
    std::deque<int> binary_search;
    for (int k = 0; k < a_cnt; k++) {
      binary_search.push_back(buf_deq[k * item_size]);
    }
    int insertion_idx = binary_insertion_deq(pair_Key, binary_search) + 1;
    for (int k = a_cnt * item_size - 1;
         k >= insertion_idx * static_cast<int>(item_size); --k) {
      buf_deq[k + item_size] = buf_deq[k];
    }
    std::copy(copy_start_loc, copy_start_loc + item_size,
              buf_deq_head + insertion_idx * item_size);
    a_cnt++;
  }

  for (int j = pair_num; j > jacobsthal_num[i - 1]; j--) {
    copy_start_loc = buf_deq1_head + (j - 2) * item_size;
    int pair_Key = *copy_start_loc;
    std::deque<int> binary_search;
    for (int k = 0; k < jacobsthal_num[i - 1] + pair_num - 1 + is_size_odd;
         k++) {
      binary_search.push_back(buf_deq[k * item_size]);
    }
    int insertion_idx = binary_insertion_deq(pair_Key, binary_search) + 1;
    for (int k = a_cnt * item_size - 1;
         k >= insertion_idx * static_cast<int>(item_size); --k) {
      buf_deq[k + item_size] = buf_deq[k];
    }
    std::copy(copy_start_loc, copy_start_loc + item_size,
              buf_deq_head + insertion_idx * item_size);
    a_cnt++;
  }

  std::copy(buf_deq_head, buf_deq_head + item_num * item_size, origin_deq_head);
  return;
}

void PmergeMe::print_vec(void) const {
  std::vector<int>::const_iterator vec_head = origin_vec.begin();
  std::vector<int>::const_iterator vec_tail = origin_vec.end();

  for (; vec_head != vec_tail; ++vec_head) {
    std::cout << *vec_head << ' ';
  }
  std::cout << '\n';
}

void PmergeMe::print_deq(void) const {
  std::deque<int>::const_iterator deq_head = origin_deq.begin();
  std::deque<int>::const_iterator deq_tail = origin_deq.end();

  for (; deq_head != deq_tail; ++deq_head) {
    std::cout << *deq_head << ' ';
  }
  std::cout << '\n';
}

void PmergeMe::print_vec_time(void) const {
  std::cout << "Time to process a range of " << origin_vec.size()
            << " elements with std::vector : " << time_calc(end_vec, start_vec)
            << "us\n";
}

void PmergeMe::print_deq_time(void) const {
  std::cout << "Time to process a range of " << origin_deq.size()
            << " elements with std::deque  : " << time_calc(end_deq, start_deq)
            << "us\n";
}

long binary_insertion_vec(int target, const std::vector<int>& bs) {
  long low = 0L;
  long high = bs.size() - 1L;
  long mid;

  while (low <= high) {
    mid = (low + high) / 2;

    if (target < bs[mid]) {
      high = mid - 1;
    } else if (target > bs[mid]) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return high;
}

long binary_insertion_deq(int target, const std::deque<int>& bs) {
  long low = 0L;
  long high = bs.size() - 1L;
  long mid;

  while (low <= high) {
    mid = (low + high) / 2;

    if (target < bs[mid]) {
      high = mid - 1;
    } else if (target > bs[mid]) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return high;
}

inline long time_calc(timeval t1, timeval t2) {
  return ((t1.tv_sec - t2.tv_sec) * S_TO_US + (t1.tv_usec - t2.tv_usec));
}