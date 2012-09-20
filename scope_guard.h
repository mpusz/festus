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

#include <utility>

template<class Fun>
class scope_guard {
  Fun _f;
  bool _active;

  scope_guard(const scope_guard &);            // disallowed
  scope_guard &operator=(const scope_guard &); // disallowed;
public:
  scope_guard(Fun f): _f(std::move(f)), _active(true) {}
  scope_guard(scope_guard &&rhs):
    _f(std::move(rhs._f)), _active(rhs._active)
  { rhs.dismiss(); }
  ~scope_guard() { if(_active) _f(); }
  void dismiss() { _active = false; }
};


template<class Fun>
inline scope_guard<Fun> make_scope(Fun f)
{ return scope_guard<Fun>(std::move(f)); }


#define CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1, s2)
#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(str) CONCATENATE(str, __COUNTER__)
#else
#define ANONYMOUS_VARIABLE(str) CONCATENATE(str, __LINE__)
#endif

namespace detail {
  
  enum class scope_guard_on_exit {};
  
  template<typename Fun>
  scope_guard<Fun>
  operator+(scope_guard_on_exit, Fun &&fn)
  { return scope_guard<Fun>(std::forward<Fun>(fn)); }
  
}

#define SCOPE_EXIT                                                      \
  auto ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) = ::detail::scope_guard_on_exit() + [&]()
