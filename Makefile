
CXX = `fltk-config --cxx`
CXXFLAGS = `fltk-config --cxxflags`
FLTKLIBS = `fltk-config --libs`
LDFLAGS = `fltk-config --ldflags`
OBJ = main.o OmmiKommTextfield.o AutopoweroffState.o ConfigState.o HelpState.o NormaleState.o OKConfig.o
BINDIR = bin
INCLUDES = -Iinclude
XMLXXINCL = `pkg-config --cflags libxml++-2.6`

VPATH = src:src/config:src/help:src/textfield

all: ommikomm

ommikomm: $(OBJ)
	$(CXX) $(CXXFLAGS) -L$(FLTKLIBS) -o $(BINDIR)/$@ $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(XMLXXINCL) -c $<
	
%.mo: %.po
	msgfmt -o $@ $<
	
.PHONY: clean update-po update-mo
	
clean:
	rm -Rf *.o
	rm bin/ommikomm
	
update-po:
	find . -iname "*.cpp" | xargs xgettext -o po/ommikomm.pot -k_ -L C++ -d ommikomm
	msgmerge -U po/de/ommikomm.po po/ommikomm.pot

update-mo: po/de/ommikomm.mo
	
