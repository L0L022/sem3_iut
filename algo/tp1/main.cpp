#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>
#include <regex>
#include <string>
#include <unordered_map>

using namespace std;

typedef wchar_t Char;

template <template <class, class...> class Map>
Map<basic_string<Char>, size_t> count_words(basic_istream<Char> &is) {
  Map<basic_string<Char>, size_t> words;
  // std::basic_regex<Char> regexp_rm(
  //     L"\\^|\\$|\\\\|\\.|\\*|\\+|\\?|\\(|\\)|\\[|\\]|\\{|\\}|\\||,|;");
  std::basic_regex<Char> regexp_rm(L"[\u2000-\u206F\u2E00-\u2E7F\\'!\"#$%&()*+,"
                                   L"\\-.\\/:;<=>?@\\[\\]^_`{|}~]"); //
  // regexp_rm.imbue(locale(""));
  // https://stackoverflow.com/questions/4328500/how-can-i-strip-all-punctuation-from-a-string-in-javascript-using-regex
  auto my_tolower = bind(tolower<Char>, placeholders::_1, locale(""));

  for (basic_string<Char> word; is.good();) {
    is >> word;
    transform(word.begin(), word.end(), word.begin(), my_tolower);
    word = regex_replace(word, regexp_rm, L"");
    try {
      words.at(word)++;
    } catch (const out_of_range &e) {
      words[word] = 1;
    }
  }

  return words;
}

int main() {
  setlocale(LC_ALL, "");

  basic_ifstream<Char> file("jules.txt");
  file.imbue(locale(""));

  unordered_map<basic_string<Char>, size_t> words;
  words = count_words<unordered_map>(file);

  for (auto &p : words)
    wcout << p.first << " " << p.second << "\n";

  return 0;
}
