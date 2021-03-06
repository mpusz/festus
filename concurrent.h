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

#include "concurrent_queue.h"
#include <future>
#include <queue>


namespace detail {

  template<typename Future, typename F, typename T>
  void set_value(std::promise<Future> &p, F &f, T &t)
  { p.set_value(f(t)); }
    
  template<typename F, typename T>
  void set_value(std::promise<void> &p, F &f, T &t)
  { f(t); p.set_value(); }
    
}
  
template<class T>
class concurrent {
  mutable T _t;
  mutable concurrent_queue<std::function<void()>> _q;
  bool _done;
  std::thread _thd;
public:
  concurrent(T t=T{}):
    _t(t), _done(false), _thd([=]{ while(!this->_done) _q.pop()(); }) {}
  ~concurrent()
  { _q.push([=]{ _done = true; }); _thd.join(); }
  template<typename F>
  auto operator()(F f) const -> std::future<decltype(f(_t))>
  {
    auto p = std::make_shared<std::promise<decltype(f(_t))> >();
    auto ret = p->get_future();
    _q.push([=]{ 
        try        { detail::set_value(*p, f, _t); }
        catch(...) { p->set_exception(std::current_exception()); }
      });
    return ret;
  }
};
