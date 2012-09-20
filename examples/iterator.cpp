/*
 * Copyright (c) 2012 Mateusz Pusz
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "iterator.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
  const char text[] = "This is cbegin() and cend() test text\n";
  std::string string("This is cbegin() and cend() test string\n");
  std::vector<int> ints;
  for(size_t i=0; i<10; i++)
    ints.push_back(i);

  std::for_each(cbegin(text),   cend(text),   [](char c){ std::cout << c; });
  std::for_each(cbegin(string), cend(string), [](char c){ std::cout << c; });
  std::for_each(cbegin(ints),   cend(ints),   [](int i) { std::cout << i << "\n"; });
}
