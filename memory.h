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

#include <memory>

#ifndef _MSC_VER

template<typename T, typename ...Args>
inline std::unique_ptr<T> make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#else

template<typename T>
inline std::unique_ptr<T>
make_unique()
{
  return std::unique_ptr<T>(new T());
}

template<typename T, typename A1>
inline std::unique_ptr<T>
make_unique(A1 &&a1)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1)));
}

template<typename T, typename A1, typename A2>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2)));
}

template<typename T, typename A1, typename A2, typename A3>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2, A3 &&a3)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2),
                                  std::forward<A3>(a3)));
}

template<typename T, typename A1, typename A2, typename A3, typename A4>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2, A3 &&a3, A4 &&a4)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2),
                                  std::forward<A3>(a3),
                                  std::forward<A4>(a4)));
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2, A3 &&a3, A4 &&a4, A5 &&a5)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2),
                                  std::forward<A3>(a3),
                                  std::forward<A4>(a4),
                                  std::forward<A5>(a5)));
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5,
         typename A6>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2, A3 &&a3, A4 &&a4, A5 &&a5, A6 &&a6)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2),
                                  std::forward<A3>(a3),
                                  std::forward<A4>(a4),
                                  std::forward<A5>(a5),
                                  std::forward<A6>(a6)));
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5,
         typename A6, typename A7>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2, A3 &&a3, A4 &&a4, A5 &&a5, A6 &&a6, A7 &&a7)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2),
                                  std::forward<A3>(a3),
                                  std::forward<A4>(a4),
                                  std::forward<A5>(a5),
                                  std::forward<A6>(a6),
                                  std::forward<A7>(a7)));
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5,
         typename A6, typename A7, typename A8>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2, A3 &&a3, A4 &&a4, A5 &&a5, A6 &&a6, A7 &&a7, A8 &&a8)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2),
                                  std::forward<A3>(a3),
                                  std::forward<A4>(a4),
                                  std::forward<A5>(a5),
                                  std::forward<A6>(a6),
                                  std::forward<A7>(a7),
                                  std::forward<A8>(a8)));
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5,
         typename A6, typename A7, typename A8, typename A9>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2, A3 &&a3, A4 &&a4, A5 &&a5, A6 &&a6, A7 &&a7, A8 &&a8, A9 &&a9)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2),
                                  std::forward<A3>(a3),
                                  std::forward<A4>(a4),
                                  std::forward<A5>(a5),
                                  std::forward<A6>(a6),
                                  std::forward<A7>(a7),
                                  std::forward<A8>(a8),
                                  std::forward<A9>(a9)));
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5,
         typename A6, typename A7, typename A8, typename A9, typename A10>
inline std::unique_ptr<T>
make_unique(A1 &&a1, A2 &&a2, A3 &&a3, A4 &&a4, A5 &&a5, A6 &&a6, A7 &&a7, A8 &&a8, A9 &&a9, A10 &&a10)
{
  return std::unique_ptr<T>(new T(std::forward<A1>(a1),
                                  std::forward<A2>(a2),
                                  std::forward<A3>(a3),
                                  std::forward<A4>(a4),
                                  std::forward<A5>(a5),
                                  std::forward<A6>(a6),
                                  std::forward<A7>(a7),
                                  std::forward<A8>(a8),
                                  std::forward<A9>(a9),
                                  std::forward<A9>(a10)));
}

#endif
