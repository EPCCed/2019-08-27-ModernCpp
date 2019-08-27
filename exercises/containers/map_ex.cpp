#include "map_ex.hpp"

bool AddWord(Word2Len& wlen_map, std::string const& word) {
  auto [iter, ans] = wlen_map.try_emplace(word, word.size());
  //wlen_map[word] = word.size();
  return ans;
}
