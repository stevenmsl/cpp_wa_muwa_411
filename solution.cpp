#include "solution.h"
#include "util.h"
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
#include <math.h>
using namespace Sol411;
using namespace std;

/*takeaways
  - this approach is based on the combination of cpp_wa_ga_320
    and cpp_wa_vwa_408's approaches
  - a min heap to store all abbreviations that can be generated
    from the target word by their size
  - start from the shortest abbreviation and see if any entry
    in the dictionary can be abbreviated to it. Continue the
    process until you can find one that can't be abbreviated
    to by any entry in the dict
*/

/*check cpp_wa_ga_320 for more detailed explanation */
priority_queue<pair<int, string>, vector<pair<int, string>>,
               greater<pair<int, string>>>
Solution::generate(string target)
{
  /* min heap with the shortest abbreviation on top
   */
  auto q = priority_queue<pair<int, string>, vector<pair<int, string>>,
                          greater<pair<int, string>>>();
  const int n = target.size();
  for (auto i = 0; i < pow(2, n); i++)
  {
    auto c = string("");
    auto cnt = 0,
         /*you need to track the size of the abbreviation
           separately and can't just use c.size()
           - ab32d the size is considered to be 4 instead
             of 5 per the question
         */
        size = 0;
    for (auto j = 0; j < n; j++)
    {
      if ((i >> j) & 1)
        cnt++;
      /*start abbreviating the previous chars and keep
        the current one
      */
      else
      {
        if (cnt)
        {
          c += to_string(cnt);
          size++;
          cnt = 0;
        }
        c += target[j];
        size++;
      }
    }

    /* for case like 11111, nothing has been abbreviated yet
       up to this point
    */
    if (cnt > 0)
    {
      c += to_string(cnt);
      size++;
    }

    q.push({size, c});
  }

  return q;
}

/* check cpp_wa_vwa_408 for more detailed explanation */
bool Solution::canAbbr(string word, string abbr)
{
  int i = 0, j = 0, m = word.size(), n = abbr.size();
  auto isDigit = [](char c)
  {
    return c >= '0' && c <= '9';
  };

  while (i < m && j < n)
  {
    if (isDigit(abbr[j]))
    {
      /* a number can't start with a leading zero */
      if (abbr[j] == '0')
        return false;
      /*how many chars we need to skip on "word" */
      int skip = 0;
      /* produce the number */
      while (j < n && isDigit(abbr[j]))
      {
        /*compse the number
          - '1'-'0' = 1
        */
        skip = skip * 10 + (abbr[j++] - '0');
      }
      /* move i ahead of "skip" chars */
      i += skip;
    }
    /* both i and j needs to point to the same char
       if j is not pointing at a digit char
    */
    else if (word[i++] != abbr[j++])
      return false;
  }

  return i == m && j == n;
}

string Solution::findMin(string &target, vector<string> &dict)
{
  if (dict.empty())
    return to_string(dict.size());
  /*q is a min heap */
  auto q = generate(target);
  while (!q.empty())
  {
    auto abbr = q.top().second;
    q.pop();
    auto hasConflict = false;
    for (auto entry : dict)
    {
      /* see if this entry can be abbreviated to abbr */
      if (canAbbr(entry, abbr))
      {
        hasConflict = true;
        break;
      }
    }
    if (!hasConflict)
      return abbr;
  }

  return "";
}