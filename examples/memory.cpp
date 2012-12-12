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

#include "memory.h"
#include <iostream>
#include <stdexcept>
#include <random>

class X {
public:
  X(int throwPrecent)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    if(dis(gen) < throwPrecent)
      throw std::runtime_error("Testing RAII");
    std::cout << "X::X()\n";
  }
  X(const X&) { std::cout << "X::X(const X&)\n"; }
  X(X&&) { std::cout << "X::X(X&&)\n"; }
  ~X() { std::cout << "X::~X()\n"; }
};


int main()
{
  try {
    auto pair = std::make_pair(make_unique<X>(50), make_unique<X>(50));
    auto array = make_unique<X[]>(50, 20);
  }
  catch(const std::exception &ex) {
    std::cout << "Exception: " << ex.what() << std::endl;
  }
}
