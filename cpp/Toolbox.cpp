#include "Toolbox.hpp"

void skip_line(std::istream &is) {
  while (is.get() != '\n' && is.good())
    ;
}

void skip_comments(std::istream &is) {
  char c = is.get();
  for (; c == '#' && is; c = is.get())
    skip_line(is);
  is.putback(c);
}
