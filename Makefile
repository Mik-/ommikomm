
CXX = `fltk-config --cxx`
CXXFLAGS = `fltk-config --cxxflags`
FLTKLIBS = `fltk-config --libs`
LDFLAGS = `fltk-config --ldflags`
OBJ = main.o AutopoweroffState.o ConfigState.o HelpState.o NormaleState.o OKConfig.o
BINDIR = bin
INCLUDES = -Iinclude

VPATH = src

all: ommikomm

ommikomm: $(OBJ)
	$(CXX) $(CXXFLAGS) -L$(FLTKLIBS) -o $(BINDIR)/$@ $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<
	
clean:
	rm -Rf *.o
	rm bin/ommikomm
