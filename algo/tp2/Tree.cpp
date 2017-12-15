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
    //std::cout << "[node: " << node << " parent: " << node->parent << " left: " << node->left << " right: " << node->right << " value: " << node->value << "] ";
    std::cout << reinterpret_cast<size_t>(node) << " [label=\"<f0> |<f1> " << node->value << "|<f2> \"];\n";
    if (node->left)
      std::cout << "\"" << reinterpret_cast<size_t>(node) << "\":f0 -> \"" << reinterpret_cast<size_t>(node->left) << "\":f1;\n";
    if (node->right)
      std::cout << "\"" << reinterpret_cast<size_t>(node) << "\":f2 -> \"" << reinterpret_cast<size_t>(node->right) << "\":f1;\n";
    disp(node->right);
  }
}

Node::Ptr Tree::create(const Node::T& value) const
{
  return new Node(value);
}

Node::Ptr Tree::find(const Node::T& value, const Node::Ptr& node) const
{
  Node::Ptr n = node;
  while (n != nullptr and n->value != value) {
    if (n->value < value)
      n = n->right;
    else if (value < n->value)
      n = n->left;
  }
  return n;
}

Node::Ptr Tree::insert(const Node::T& value, Node::Ptr& node) const
{
  Node::Ptr p = node;
  Node::Ptr* n = &node;
  while (*n != nullptr) {
    if ((*n)->value == value) {
      return *n;
    } else if ((*n)->value < value) {
      p = *n;
      n = &(*n)->right;
    } else {
      p = *n;
      n = &(*n)->left;
    }
  }
  *n = create(value);
  (*n)->parent = p;
  return *n;
}
