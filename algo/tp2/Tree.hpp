#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"

class Tree
{
public:
  Tree();
  ~Tree();

  void disp(const Node::Ptr& node) const;

  Node::Ptr create(const Node::T& value) const;
  Node::Ptr find(const Node::T& value, const Node::Ptr& node) const;
  Node::Ptr insert(const Node::T& value, Node::Ptr& node) const;

  Node::Ptr _root;
};

#endif
