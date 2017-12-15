#include "Tree.hpp"
#include <iostream>

Tree::Tree()
: _root(nullptr)
{}

Tree::~Tree()
{
  delete _root;
}

void Tree::disp(const Node::Ptr& node) const
{
  if (node) {
    disp(node->left);
    std::cout << node->value << ", ";
    disp(node->right);
  }
}

Node::Ptr Tree::create(const Node::T& value) const
{
  return new Node(value);
}

Node::Ptr Tree::find(const Node::T& value, const Node::Ptr& node) const
{
  // if (node) {
  //   if (node->value == value)
  //     return node;
  //   else if (node->value < value)
  //     return find(value, node->right);
  //   else
  //     return find(value, node->left);
  // }
  // return nullptr;

  Node::Ptr n = node;
  while (n != nullptr and n->value != value) {
    std::cout << n->value << '\n';
    if (node->value < value)
      n = node->right;
    else if (value < node->value)
      n = node->left;
  }
  return n;
}

Node::Ptr Tree::insert(const Node::T& value, Node::Ptr& node) const
{
  Node::Ptr* n = &node;
  while (*n != nullptr) {
    if ((*n)->value == value)
      return *n;
    else if ((*n)->value < value)
      n = &(*n)->right;
    else
      n = &(*n)->left;
  }
  return *n = create(value);
}
