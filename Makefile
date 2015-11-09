CC = g++
LINKER = g++
CFLAGS =-c -Wall
LDFLAGS = 
MAIN = test.cpp
EXE = test.out

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPFILES = $(SOURCES:.cpp=.d)

all:$(EXE)

$(EXE):$(OBJECTS)
	$(LINKER) $(LDFLAGS) $(OBJECTS) -o $@

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.d: %.cpp
	$(CC) -MM $< | sed 's/^/$@ /' > $@

-include $(DEPFILES)

clean:
	rm $(EXE) $(OBJECTS) $(DEPFILES)
