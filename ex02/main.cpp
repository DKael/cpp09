#include "PmergeMe.hpp"

int main(const int argc, const char** argv) {
  if (argc == 1) {
    std::cout << "Usage : " << argv[0] << " num_1 num_2 num_3 ... num_n\n";
    exit(1);
  }

  try {
    PmergeMe::PmergeMe_init();
    PmergeMe salt(argc - 1, &argv[1]);

    std::cout << "<Before merge insertion sort>\nstd::vector : ";
    salt.print_vec();
    std::cout << "std::deque  : ";
    salt.print_deq();

    salt.merge_insertion_sort();

    std::cout << "<After merge insertion sort>\nstd::vector : ";
    salt.print_vec();
    std::cout << "std::deque  : ";
    salt.print_deq();
    salt.print_vec_time();
    salt.print_deq_time();
  } catch (const std::exception& e) {
    std::cout << e.what() << '\n';
    exit(1);
  }
}
