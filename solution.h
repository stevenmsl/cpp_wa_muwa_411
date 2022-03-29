#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;
namespace Sol411
{
  class Solution
  {
  private:
    static priority_queue<pair<int, string>, vector<pair<int, string>>,
                          greater<pair<int, string>>>
    generate(string target);
    static bool canAbbr(string word, string abbr);

  public:
    static string findMin(string &target, vector<string> &dict);
  };
}
#endif