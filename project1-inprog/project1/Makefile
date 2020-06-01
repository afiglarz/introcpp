CXXFLAGS = -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -std=c++11

SOURCES = proj1.cpp proj1image.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
BINARY = project1
LIB = libproject1image.so
DYNAMIC = dynamic_proj1

all: $(BINARY) $(LIB) $(DYNAMIC)

$(BINARY): $(OBJECTS)
	$(CXX) $^ -o $@

$(LIB): proj1image.o
	$(CXX) -shared -fPIC proj1image.o -o libproject1image.so

$(DYNAMIC): proj1.o libproject1image.so
	$(CXX) proj1.o -o dynamic_proj1 -L. -lproject1image

clean:
	$(RM) $(BINARY) $(OBJECTS) $(LIB) $(DYNAMIC)

