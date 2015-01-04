bin_PROGRAMS = ommikomm
ommikomm_SOURCES = main.cpp src/NormaleState.cpp src/AutopoweroffState.cpp src/config/ConfigState.cpp src/config/OKConfig.cpp src/config/OKConfigPersistent.cpp src/help/HelpState.cpp src/textfield/OmmiKommTextfield.cpp
ommikomm_CPPFLAGS = $(LIBXMLXX_CFLAGS)
ommikomm_LDADD = -lfltk $(LIBXMLXX_LIBS)

SUBDIRS = . po

AUTOMAKE_OPTIONS = subdir-objects 

localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath

check-gettext:
	@if test x$(USE_NLS) != "xyes" ; then echo "Missing gettext. Rerun configure and check for" \
	"'checking whether to use NLS... yes'!" ; exit 1 ; fi

update-po: check-gettext
	@find $(srcdir)/src/ -name "*.cpp" -print | sort > $(srcdir)/po/POTFILES.in.2 ; \
	if diff $(srcdir)/po/POTFILES.in $(srcdir)/po/POTFILES.in.2 >/dev/null 2>&1 ; then \
		rm -f $(srcdir)/po/POTFILES.in.2 ; \
	else \
		mv $(srcdir)/po/POTFILES.in.2 $(srcdir)/po/POTFILES.in ; \
	fi
	cd po && $(MAKE) $(AM_MAKEFLAGS) update-po

update-gmo: check-gettext
	cd po && $(MAKE) $(AM_MAKEFLAGS) update-gmo

force-update-gmo: check-gettext
	touch po/*.po
	cd po && $(MAKE) $(AM_MAKEFLAGS) update-gmo

force-update-gmo-%: check-gettext
	@language=`echo $@ | sed s/force-update-gmo-//` ; \
	if test ! -f po/$$language.po ; then echo "file po/$$language.po does not exist" ; exit 1 ; fi ; \
	touch po/$$language.po ; \
	cd po && $(MAKE) $(AM_MAKEFLAGS) update-gmo

.PHONY: check-gettext update-po update-gmo force-update-gmo