CXXFLAGS = -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -std=c++11

SOURCES = proj1.cpp 
OBJECTS = $(SOURCES:%.cpp=%.o)
BINARY = project1

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $< -o $@
