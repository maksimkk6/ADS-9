// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include "tree.h"

namespace {
int64_t factorial(int n) {
  int64_t res = 1;
  for (int i = 2; i <= n; i++) {
    res *= i;
  }
  return res;
}

void dfsPerms(PMNode* node,
              std::vector<char>& current,
              std::vector<std::vector<char>>& result) {
  if (node->value != '\0') {
    current.push_back(node->value);
  }

  if (node->children.empty()) {
    if (!current.empty()) {
      result.push_back(current);
    }
  } else {
    for (PMNode* child : node->children) {
      dfsPerms(child, current, result);
    }
  }

  if (node->value != '\0') {
    current.pop_back();
  }
}
}

PMTree::PMTree(const std::vector<char>& elems) {
  alphabet_ = elems;
  root_ = new PMNode();

  buildTree(root_, elems);
}

PMTree::~PMTree() {
  deleteTree(root_);
}

void PMTree::deleteTree(PMNode* node) {
  if (node == nullptr) {
    return;
  }

  for (PMNode* child : node->children) {
    deleteTree(child);
  }

  delete node;
}

void PMTree::buildTree(PMNode* node,
                       const std::vector<char>& elems) {
  if (elems.empty()) {
    return;
  }

  for (size_t i = 0; i < elems.size(); i++) {
    PMNode* child = new PMNode(elems[i]);
    node->children.push_back(child);

    std::vector<char> rest;

    for (size_t j = 0; j < elems.size(); j++) {
      if (j != i) {
        rest.push_back(elems[j]);
      }
    }

    buildTree(child, rest);
  }
}

PMNode* PMTree::getRoot() const {
  return root_;
}

const std::vector<char>& PMTree::getAlphabet() const {
  return alphabet_;
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;

  dfsPerms(tree.getRoot(), current, result);

  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> perms = getAllPerms(tree);

  if (num <= 0 || num > static_cast<int>(perms.size())) {
    return {};
  }

  return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  const std::vector<char>& alphabet = tree.getAlphabet();

  int n = static_cast<int>(alphabet.size());

  int64_t total = factorial(n);

  if (num <= 0 || num > total) {
    return {};
  }

  int k = num - 1;

  std::vector<char> available = alphabet;
  std::vector<char> result;

  for (int pos = n; pos >= 1; pos--) {
    int64_t block = factorial(pos - 1);

    int index = static_cast<int>(k / block);
    k %= block;

    result.push_back(available[index]);
    available.erase(available.begin() + index);
  }

  return result;
}
