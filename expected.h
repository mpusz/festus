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

#include <exception>
#include <utility>


template<class T>
class expected {
  union {
    T _t;
    std::exception_ptr _ex;
  };
  bool _isT;
public:
  expected(const T &t): _t{t}, _isT{true} {}

  expected(T &&t): _t{std::move(t)}, _isT{true} {}

  template<class E>
  expected(const E &e,
           typename std::enable_if<std::is_base_of<std::exception,E>::value,
                                   void*>::type = 0): _isT{false}
  { new(&_ex) std::exception_ptr(std::make_exception_ptr(e)); }
  
  expected(const expected &rhs): _isT{rhs.gotT}
  {
    if(_isT) new(&_t) T(rhs._t);
    else new(&_ex) std::exception_ptr(rhs._ex);
  }
  
  expected(expected &&rhs): _isT{std::move(rhs._isT)}
  {
    if(_isT) new(&_t) T(std::move(rhs._t));
    else new(&_ex) std::exception_ptr(std::move(rhs._ex));
  }

  ~expected()
  {
    if(_isT) _t.~T();
    else _ex.~exception_ptr();
  }

  void swap(expected &rhs)
  {
    if(_isT) {
      if(rhs._isT) {
        using std::swap;
        swap(_t, rhs._t);
      }
      else {
        auto ex = std::move(rhs._ex);
        new(&rhs._t) T(std::move(_t));
        new(&_ex) std::exception_ptr(ex);
        std::swap(_isT, rhs._isT);
      }
    }
    else {
      if(rhs._isT) {
        rhs.swap(*this);
      }
      else {
        _ex.swap(rhs._ex);
        std::swap(_isT, rhs._isT);
      }
    }
  }
  
  bool valid() const { return _isT; }
  
  T &get()
  {
    if(!_isT) std::rethrow_exception(_ex);
    return _t;
  }
  
  const T &get() const
  {
    if(!_isT) std::rethrow_exception(_ex);
    return _t;
  }
  
  template<class E>
  bool hasException() const
  {
    try {
      if(!_isT) std::rethrow_exception(_ex);
    }
    catch(const E &object) {
      return true;
    }
    catch (...) {
    }
    return false;
  }
  
  template<class F>
  static expected fromCode(F fun)
  {
    try {
      return expected(fun());
    }
    catch(...) {
      return expected(std::current_exception());
    }
  }
};
