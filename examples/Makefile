#
# Copyright (c) 2012 Mateusz Pusz
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

CPP_FILES := concurrent.cpp expected.cpp iterator.cpp memory.cpp monitor.cpp scope_guard.cpp then.cpp
TARGET_FILES := $(patsubst %.cpp,%,$(CPP_FILES))

#CXX      := /usr/lib/gcc-snapshot/bin/g++
#CXX      := /opt/clang-dev/bin/clang++

CXXFLAGS := $(CXXFLAGS) -Wall -std=c++11
INCLUDES := $(INCLUDES) -I..
LIBS     := -lpthread

.PHONY: all clean

all: $(TARGET_FILES)

clean:
	$(RM) $(TARGET_FILES)

%: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MD -MF $*.d $< -o $@ $(LIBS)

# include depends files
-include $(CPP_FILES:.cpp=.d))
