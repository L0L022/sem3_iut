#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>
#include <locale>
#include <algorithm>
#include <functional>

using namespace std;

typedef wchar_t Char;

template <template<class, class...> class Map>
Map<basic_string<Char>, size_t> count_words(basic_istream<Char>& is)
{
  basic_string<Char> word;
  Map<basic_string<Char>, size_t> words;
  std::basic_regex<Char> regexp_rm(L"\\^|\\$|\\\\|\\.|\\*|\\+|\\?|\\(|\\)|\\[|\\]|\\{|\\}|\\||,|;");
  auto my_tolower = bind(tolower<char>, placeholders::_1, locale("fr_FR.UTF-8"));
  while (is.good()) {
    is >> word;
    word = regex_replace(word, regexp_rm, L"");
    transform(word.begin(), word.end(), word.begin(), my_tolower);
    try {
      words.at(word)++;
    } catch (const out_of_range& e) {
      words[word] = 1;
    }
  }
  return words;
}

int main()
{
  basic_ifstream<Char> file("jules.txt");

  unordered_map<basic_string<Char>, size_t> words;
  words = count_words<unordered_map>(file);
  for (auto& p : words)
    wcout << p.first << " " << p.second << "\n";

  return 0;
}
