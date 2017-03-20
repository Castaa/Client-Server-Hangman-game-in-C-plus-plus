#pragma once
#include<vector>
#include<string>

#if 0
// key comparision function for my map, std::map<const string, int>
struct ltstr
{
  bool operator()(const std::string& s1, const std::string& s2) const
  {
    return s1.compare(s2) < 0;
  }
};
#endif

bool LoadWordFile(std::vector<std::string>&);
