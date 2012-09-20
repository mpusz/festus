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

#include "monitor.h"
#include <future>
#include <iostream>
#include <vector>
#include <string>


int main()
{
  {
    monitor<std::string> s("start\n");
    std::vector<std::future<void>> v;

    for(int i=0; i<5; i++)
      v.push_back(std::async(std::launch::async, [&,i]{
            s([=](std::string &s) {
                s += std::to_string(i) + " " + std::to_string(i);
                s += "\n";
              });
            s([=](std::string &s) {
                std::cout << "thread: " << i << "\n" << s;
              });
          }));
    for(auto &f : v)
      f.wait();
    std::cout << "Done\n";
  }

  std::cout << "\n---------------------------------------\n\n";

  {
    monitor<std::ostream &> sync_cout(std::cout);
    std::vector<std::future<void> > v;
    for(int i=0; i<5; i++)
      v.push_back(std::async(std::launch::async, [&,i]{
            sync_cout([=](std::ostream &cout) {
                cout << std::to_string(i) << " " << std::to_string(i);
                cout << "\n";
              });
            sync_cout([=](std::ostream &cout) {
                cout << "Hi from " << i << std::endl;
              });
          }));
    for(auto &f : v)
      f.wait();
    sync_cout([](std::ostream &cout){ cout << "Done\n"; });
  }
}
