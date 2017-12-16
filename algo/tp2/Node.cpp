#include "Node.hpp"

Node::Node(const T& value)
: value(value)
, parent(nullptr)
, right(nullptr)
, left(nullptr)
{}

Node::~Node()
{
  delete right;
  delete left;
}
