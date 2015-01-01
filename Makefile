
CXX = `fltk-config --cxx`
CXXFLAGS = `fltk-config --cxxflags`
FLTKLIBS = `fltk-config --libs`
LDFLAGS = `fltk-config --ldflags`
OBJ = main.o OmmiKommTextfield.o AutopoweroffState.o ConfigState.o HelpState.o NormaleState.o OKConfig.o
BINDIR = bin
INCLUDES = -Iinclude
XMLXXINCL = `pkg-config --cflags libxml++-2.6`

VPATH = src

all: ommikomm

ommikomm: $(OBJ)
	$(CXX) $(CXXFLAGS) -L$(FLTKLIBS) -o $(BINDIR)/$@ $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(XMLXXINCL) -c $<
	
clean:
	rm -Rf *.o
	rm bin/ommikomm
