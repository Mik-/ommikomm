bin_PROGRAMS = ommikomm
ommikomm_SOURCES = src/main.cpp src/TypingState.cpp src/RestartState.cpp src/PINInputState.cpp src/settings/SettingsState.cpp src/settings/Settings.cpp src/settings/SettingsPersistence.cpp src/help/HelpState.cpp src/textfield/OmmiKommTextfield.cpp
ommikomm_CPPFLAGS = $(LIBXMLXX_CFLAGS)
ommikomm_LDADD = -lfltk $(LIBXMLXX_LIBS)

TESTS = check_ommikomm
check_PROGRAMS = check_ommikomm
check_ommikomm_SOURCES = tests/check_ommikomm.cpp tests/mock_config.cpp src/TypingState.cpp src/RestartState.cpp src/PINInputState.cpp src/settings/SettingsState.cpp src/settings/Settings.cpp src/settings/SettingsPersistence.cpp src/help/HelpState.cpp src/textfield/OmmiKommTextfield.cpp
check_ommikomm_CPPFLAGS = $(LIBXMLXX_CFLAGS)
check_ommikomm_LDADD = -lfltk $(LIBXMLXX_LIBS) 

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

update-testrunner:
	@if test x$(HAVE_CXXTEST) == "xno"; then echo "Missing cxxtest."; exit 1; fi
	cxxtestgen --error-printer --include=../src/config.h -o tests/check_ommikomm.cpp tests/check_persistence.cpp


.PHONY: check-gettext update-po update-gmo force-update-gmo update-testrunner
