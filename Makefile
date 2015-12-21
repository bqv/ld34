CXX=g++
CXXFLAGS=-c -Wall
LDFLAGS=-lSDL
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game

SOURCES=\
main.cpp

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@
