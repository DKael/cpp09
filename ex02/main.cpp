#include "PmergeMe.hpp"

int main(const int argc, const char** argv) {
  if (argc == 1) {
    std::cout << "Usage : " << argv[0] << " num_1 num_2 num_3 ... num_n\n";
    exit(1);
  }

  try {
    PmergeMe salt(argc - 1, &argv[1]);

    salt.print();

    salt.merge_insertion_sort();
  } catch (const std::exception& e) {
    std::cout << e.what() << '\n';
    exit(1);
  }
}