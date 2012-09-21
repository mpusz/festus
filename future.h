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

#include <future>
#include <type_traits>
#include <chrono>

namespace future {
  
  template<typename T>
  bool ready(const std::future<T> &f)
  { return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; }
  
  namespace detail {

    // Based on http://stackoverflow.com/a/7943765
    // For generic types, directly use the result of the signature of its 'operator()'
    template<typename T>
    struct function_traits : public function_traits<decltype(&T::operator())> {};
    
    // we specialize for pointers to member function
    template<typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...) const> {
      typedef ReturnType result_type;
      static const std::size_t arg_count = sizeof...(Args);
      
      template<size_t i>
      struct arg {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
      };
    };
    
    template<typename FUTURE, typename WORK>
    std::future<void> then_noreturn(FUTURE f, WORK w, std::integral_constant<size_t, 1>)
    { return std::async(std::launch::async, [w](FUTURE f) { w(f.get()); }, std::move(f)); }
    
    template<typename FUTURE, typename WORK>
    std::future<void> then_noreturn(FUTURE f, WORK w, std::integral_constant<size_t, 0>)
    { return std::async(std::launch::async, [w](FUTURE f) { f.get(); w(); }, std::move(f)); }
    
  } // namespace detail
  
  // then() implementations
  template<typename FUTURE, typename WORK,
           typename = typename std::enable_if<
             !std::is_same<void, typename detail::function_traits<WORK>::result_type>::value &&
             detail::function_traits<WORK>::arg_count == 1
             >::type>
  auto then(FUTURE f, WORK w) -> std::future<decltype(w(f.get()))>
  {
    return std::async(std::launch::async, [w](FUTURE f) { return w(f.get()); }, std::move(f));
  }
  
  template<typename FUTURE, typename WORK,
           typename = typename std::enable_if<
             !std::is_same<void, typename detail::function_traits<WORK>::result_type>::value &&
             detail::function_traits<WORK>::arg_count == 0
             >::type>
  auto then(FUTURE f, WORK w) -> std::future<decltype(w())>
  {
    return std::async(std::launch::async, [w](FUTURE f) { f.get(); return w(); }, std::move(f));
  }
  
  template<typename FUTURE, typename WORK,
           typename = typename std::enable_if<
             std::is_same<void, typename detail::function_traits<WORK>::result_type>::value>::type>
  auto then(FUTURE f, WORK w) -> std::future<void>
  {
    typedef typename std::integral_constant<size_t, detail::function_traits<WORK>::arg_count>::type argCount;
    return detail::then_noreturn(std::forward<FUTURE>(f), std::forward<WORK>(w), argCount());
  }

}
