#include <iostream>
#include <string>
#include <string_view>

using namespace std;

string hello = "4";

string str_trim(string str) {
  if(str.back() == '\n')
    str.pop_back();

  while(str.back() == ' ')
    str.pop_back();
  while(str.front() == ' ')
    str.erase(0, 1);

  return str;
}