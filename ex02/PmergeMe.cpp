#include "PmergeMe.hpp"

std::vector<std::uint64_t> PmergeMe::jacobsthal_num;

void PmergeMe::PmergeMe_init(void) {
  static bool init_flag = false;
  if (init_flag == false) {
    init_flag = true;
    jacobsthal_num.push_back(0);
    jacobsthal_num.push_back(1);
    for (int i = 1; i < 20; i++) {
      jacobsthal_num.push_back((1ULL << i) - jacobsthal_num[i]);
    }
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
    origin_vec.push_back(tmp_int);
    buf_vec.push_back(tmp_int);
    origin_deq.push_back(tmp_int);
  }
}

PmergeMe::~PmergeMe() { ; }

void PmergeMe::merge_insertion_sort(void) {
  if (origin_vec.size() < 2) {
    return;
  }
  _merge_insertion_vec(0, origin_vec.size());
}

void PmergeMe::_merge_insertion_vec(std::size_t level, std::size_t item_cnt) {
  std::size_t idx_offset = (1UL << level);
  std::size_t step = (idx_offset << 1);
  std::size_t idx = 0;
  bool is_size_odd = (item_cnt % 2UL == 1UL);

  for (std::size_t i = 0UL; i < (item_cnt / 2); i++) {
    idx = i * step;
    if (origin_vec[idx] < origin_vec[idx + idx_offset]) {
      std::copy(origin_vec.begin() + idx + idx_offset,
                origin_vec.begin() + idx + step, buf_vec.begin() + idx);
      std::copy(origin_vec.begin() + idx, origin_vec.begin() + idx + idx_offset,
                buf_vec.begin() + idx + idx_offset);
    }
  }
  std::copy(buf_vec.begin(), buf_vec.begin() + (item_cnt / 2UL) * step,
            origin_vec.begin());
  if (item_cnt / 2UL != 1UL) {
    _merge_insertion_vec(level + 1UL, item_cnt / 2UL);
  }
}

void PmergeMe::print(void) const {
  std::vector<int>::const_iterator vec_head = origin_vec.begin();
  std::vector<int>::const_iterator vec_tail = origin_vec.end();
  std::deque<int>::const_iterator deq_head = origin_deq.begin();
  std::deque<int>::const_iterator deq_tail = origin_deq.end();

  for (; vec_head != vec_tail; ++vec_head) {
    std::cout << *vec_head << ' ';
  }
  std::cout << '\n';
  for (; deq_head != deq_tail; ++deq_head) {
    std::cout << *deq_head << ' ';
  }
  std::cout << '\n';
}
