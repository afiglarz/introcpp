CXXFLAGS = -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -std=c++11

SOURCES = proj1.cpp proj1image.cpp
HEADERS = proj1header.h
OBJECTS = $(SOURCES:%.cpp=%.o)
BINARY = project1

all: $(BINARY)

$(BINARY): $(OBJECTS) $(HEADERS)
	$(CXX) $< -o $@

clean:
	$(RM) $(BINARY) $(OBJECTS)

