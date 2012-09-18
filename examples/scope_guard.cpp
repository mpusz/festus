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

#include "scope_guard.h"
#include <iostream>
#include <vector>
#include <stdexcept>


class thrower {
  static int _nextId;
  int _id;
public:
  thrower(int id): _id(id)
  { if(_nextId++ == _id) throw std::runtime_error("Index reached"); }
  friend std::ostream &operator<<(std::ostream &o, const thrower &t)
  { return o << "thrower_" << t._id; }
};

int thrower::_nextId = 2;


int main(int argc, const char *argv[])
{
  try {
    // action 0
    int *step = (int *)malloc(sizeof(int));
    // cleanup 0
    SCOPE_EXIT{ std::cout << "Releasing step\n"; free(step); };
    
    if(argc != 2) {
      std::cout << "scope_guard <exit_after_step>" << std::endl;
      throw std::runtime_error("invalid number of arguments");
    }
    *step = atoi(argv[1]);
    if(*step == 0)
      return EXIT_SUCCESS;

    // action 1
    std::vector<thrower*> data;
    // cleanup 1
    SCOPE_EXIT{ std::cout << "cleanup 1:\n"; for(auto v : data) { std::cout << " - " << *v << "\n"; delete v; } };

    if(*step == 1)
      return EXIT_SUCCESS;
  
    // action 2
    data.push_back(new thrower(*step));
    // rollback 2
    auto rollback2 = make_scope([&]{ std::cout << "rollback 2\n"; delete data.back(); data.pop_back(); });
  
    // action 3
    data.push_back(new thrower(*step));
    // rollback 3
    auto rollback3 = make_scope([&]{ std::cout << "rollback 3\n"; delete data.back(); data.pop_back(); });

    // action 4
    std::cout << "Last action\n";
    if(*step == 4)
      return EXIT_FAILURE;

    std::cout << "Success!!!\n";
  
    // all steps succeeded
    rollback3.dismiss();
    rollback2.dismiss();
  }
  catch(const std::exception &ex) {
    std::cout << "Error: " << ex.what() << std::endl;
  }
}
