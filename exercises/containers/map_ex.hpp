#ifndef CPPEX_MAP_EX_HPP
#define CPPEX_MAP_EX_HPP

#include <map>
#include <iostream>

using Word2Len = std::map<std::string, int>;

bool AddWord(Word2Len& wlen_map, std::string const& word);

#endif
