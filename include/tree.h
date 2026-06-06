// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct PMNode {
  char value;
  std::vector<PMNode*> children;

  explicit PMNode(char val = '\0') : value(val) {}
};

class PMTree {
 private:
  PMNode* root_;
  std::vector<char> alphabet_;

  void buildTree(PMNode* node, const std::vector<char>& elems);
  void deleteTree(PMNode* node);

 public:
  explicit PMTree(const std::vector<char>& elems);
  ~PMTree();

  PMNode* getRoot() const;
  const std::vector<char>& getAlphabet() const;
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);

std::vector<char> getPerm1(PMTree& tree, int num);

std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
