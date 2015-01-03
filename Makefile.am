bin_PROGRAMS = ommikomm
ommikomm_SOURCES = main.cpp src/NormaleState.cpp src/AutopoweroffState.cpp src/config/ConfigState.cpp src/config/OKConfig.cpp src/config/OKConfigPersistent.cpp src/help/HelpState.cpp src/textfield/OmmiKommTextfield.cpp
ommikomm_CPPFLAGS = $(LIBXMLXX_CFLAGS)
ommikomm_LDADD = -lfltk $(LIBXMLXX_LIBS)

AUTOMAKE_OPTIONS = subdir-objects 

localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

