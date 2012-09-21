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

#include "future.h"
#include "monitor.h"
#include <iostream>


int main()
{
  monitor<std::ostream&> sync_cout(std::cout);

  // example of futures scheduling
  sync_cout([](std::ostream &out){ out << "START\n"; });
  auto f1 = std::async(std::launch::async, [&]
                       {
                         sync_cout([](std::ostream &out){ out << "Task 1 - that was easy :-)\n"; });
                       });
  auto f2 = future::then(std::move(f1), [&]
                         {
                           static const int VAL = 123;
                           sync_cout([](std::ostream &out){ out << "Task 2 - returning " << VAL << "\n"; });
                           return VAL;
                         });
  auto f3 = future::then(std::move(f2), [&](int v)
                         {
                           const int val = 2 * v;
                           sync_cout([=](std::ostream &out){ out << "Task 3 - returning " << v << "*2=" << val << "\n"; });
                           return val;
                         });
  auto f4 = future::then(std::move(f3), [&](int v)
                         {
                           const int val = v + 9;
                           sync_cout([=](std::ostream &out){ out << "Task 4 - final result " << v << "+9=" << val << "\n"; });
                         });
  auto f5 = future::then(std::move(f4), [&]
                         {
                           sync_cout([](std::ostream &out){ out << "Task 5 - The end\n"; });
                         });
  
  // example of active waiting on future
  while(!future::ready(f5)) {
    sync_cout([](std::ostream &out){ out << "Waiting\n"; });
    //    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  }
  
  sync_cout([](std::ostream &out){ out << "FINISH\n"; });
}
