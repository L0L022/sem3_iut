#include <iostream>
#include <random>

#include "Tree.hpp"

using namespace std;

int main()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 100);

  Tree t;
  t.disp(t._root); cout << '\n';

  for (size_t i = 0; i < 60; i++) {
    t.insert(dis(gen), t._root);
    t.disp(t._root); cout << '\n';
  }
  t.insert(100, t._root);
  t.find(100, t._root)->value = 9999;
  t.disp(t._root); cout << '\n';

  return 0;
}
