#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace Sol411;

/* All Examples
"apple", ["blade"] -> "a4" (because "5" or "4e" conflicts with "blade")
"apple", ["plain", "amber", "blade"] -> "1p3" (other valid answers include "ap3", "a3e", "2p2", "3le", "3l1").
*/
tuple<string, vector<string>, vector<string>>
testFixture1()
{
  auto dict = vector<string>{"blade"};
  auto possibleResults = vector<string>{"a4"};
  return make_tuple("apple", dict, possibleResults);
}

tuple<string, vector<string>, vector<string>>
testFixture2()
{
  auto dict = vector<string>{"plain", "amber", "blade"};
  auto possibleResults = vector<string>{"1p3", "ap3", "a3e", "2p2", "3le", "3l1"};
  return make_tuple("apple", dict, possibleResults);
}

void test1()
{
  auto f = testFixture1();
  cout << "Test 1 - exepct to see one of the following: " << Util::toString(get<2>(f)) << endl;
  auto result = Solution::findMin(get<0>(f), get<1>(f));
  cout << "result: " << result << endl;
}
void test2()
{
  auto f = testFixture2();
  cout << "Test 2 - exepct to see one of the following: " << Util::toString(get<2>(f)) << endl;
  auto result = Solution::findMin(get<0>(f), get<1>(f));
  cout << "result: " << result << endl;
}

main()
{
  test1();
  test2();
  return 0;
}