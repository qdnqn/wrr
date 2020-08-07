EXE = wrr
SOURCES = wrr.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

CXX = g++
CXXFLAGS = 
LIBS =

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $?

clean:
	rm -f *.o
	rm -f $(EXE)
