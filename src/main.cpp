// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include "tree.h"
int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);
  std::cout << "Perm #1 (getPerm1): ";
  auto p1 = getPerm1(tree, 1);
  for (char c : p1) {
    std::cout << c;
  }
  std::cout << std::endl;
  std::cout << "Perm #2 (getPerm2): ";
  auto p2 = getPerm2(tree, 2);
  for (char c : p2) {
    std::cout << c;
  }
  std::cout << std::endl;

  return 0;
}
