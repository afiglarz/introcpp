CXXFLAGS = -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -std=c++11 -fPIC -I/Users/aef1/NIST/libbiomeval/src/include
LDFLAGS = -L/Users/aef1/NIST/libbiomeval/lib -lbiomeval.dylib

SOURCES = frameworkpractice.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
BINARY = project2

all: $(BINARY) 

$(BINARY): $(OBJECTS)
	$(CXX) $^ -o $@

clean:
	$(RM) $(BINARY) $(OBJECTS) 

