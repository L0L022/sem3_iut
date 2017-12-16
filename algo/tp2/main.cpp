#include <iostream>
#include <random>

#include "Tree.hpp"

using namespace std;

int main()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 200);

  Tree t;
  // t.disp(t._root); cout << '\n';
  t.insert(50, t._root);
  for (size_t i = 0; i < 1000; i++) {
    t.insert(dis(gen), t._root);
    // t.disp(t._root); cout << '\n';
  }
  t.insert(0, t._root);

  cout << "digraph G {\nnode [shape = record,height=.1];\n";
  t.disp(t._root); cout << '\n';
  cout << "}\n";
  //cout << "value " << t.find(0, t._root)->value << '\n';

  return 0;
}
