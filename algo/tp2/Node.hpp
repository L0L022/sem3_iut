#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node
{
  public:
  typedef size_t T;
  typedef Node* Ptr;

  T value;
  Ptr parent;
  Ptr right;
  Ptr left;

  Node(const T& value = T());
  ~Node();

  bool isRoot() const { return parent == nullptr; }
  bool isLeaf() const { return right == nullptr and left == nullptr; }
  bool isBranch() const { return right != nullptr or left != nullptr; }
};

#endif
