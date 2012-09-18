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

#include "expected.h"
#include <string>
#include <stdexcept>
#include <iostream>


expected<int> parseInt(const std::string &s)
{
  if(s == "nan")
    return std::invalid_argument("not a number");
  //...
  if(s == "overflow")
    return std::out_of_range("overflow");
  //...
  return atoi(s.c_str());
}


int testExceptions(const std::string &argument)
{
  try {
    std::cout << "Provide an integer to parse (or 'nan' or 'overflow'): ";
    std::string s;
    std::cin >> s;
    auto x = parseInt(s).get(); // throw on error
    std::cout << "Value: " << x << std::endl;
    return EXIT_SUCCESS;
  }
  catch(const std::invalid_argument &) {
    std::cout << "Sorry, I was expecting a number.\n";
    return EXIT_FAILURE;
  }
  catch(const std::exception &ex) {
    std::cout << "Error: Unknown error: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}


int testErrors(const std::string &argument)
{
  std::cout << "Provide an integer to parse (or 'nan' or 'overflow'): ";
  std::string s;
  std::cin >> s;
  auto exp = parseInt(s); // won’t throw
  if(exp.valid()) {
    std::cout << "Value: " << exp.get() << std::endl;
    return EXIT_SUCCESS;
  }
  else {
    // handle locally
    if(exp.hasException<std::invalid_argument>()) {
      std::cout << "Sorry, I was expecting a number.\n";
      return EXIT_FAILURE;
    }
    
    try {
      exp.get(); // just "re"throw
    }
    catch(const std::exception &ex) {
      std::cout << "Error: Unknown error: " << ex.what() << std::endl;
      return EXIT_FAILURE;
    }
    return EXIT_FAILURE;
  }
}


int main(int argc, const char *argv[])
{
  if(argc == 2) {
    std::string argument(argv[1]);
    if(argument == "exceptions")
      return testExceptions(argument);
    else if(argument == "errors")
      return testErrors(argument);
  }
  else {
    std::cout << "Usage: expected <exceptions|errors>\n";
    return EXIT_SUCCESS;
  }
}
