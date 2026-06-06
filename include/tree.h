// Copyright 2022 NNTU-CS
#ifndef TREE_H
#define TREE_H
#include <vector>
class PMTree {
 public:
  struct Node {
    char value;
    std::vector<Node*> childs;
    Node(char v = 0) : value(v) {}
  };
  Node* root;
  int alphabetSize;

  explicit PMTree(const std::vector<char>& data) {
    root = new Node(0);
    alphabetSize = static_cast<int>(data.size());
    build(root, data);
  }
  ~PMTree() {
    clear(root);
  }
 private:
  void build(Node* parent, const std::vector<char>& symbols) {
    if (symbols.empty())
      return;
    for (size_t i = 0; i < symbols.size(); i++) {
      Node* node = new Node(symbols[i]);
      parent->childs.push_back(node);
      std::vector<char> next;
      for (size_t j = 0; j < symbols.size(); j++)
        if (j != i)
          next.push_back(symbols[j]);
      build(node, next);
    }
  }

  void clear(Node* node) {
    if (!node)
      return;

    for (auto x : node->childs)
      clear(x);

    delete node;
  }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif
