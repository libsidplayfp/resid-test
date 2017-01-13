
ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = foreign subdir-objects


if MINGW32
  W32_CPPFLAGS = -DWIN32_LEAN_AND_MEAN
  W32_LDFLAGS = -no-undefined
endif


AM_CPPFLAGS = -I $(top_srcdir)/src \
-I $(top_builddir)/src/resid \
${W32_CPPFLAGS} \
@debug_flags@ \
-DVERSION=\"1.0-pre2\"

AM_CFLAGS = -std=c99

#=========================================================
EXTRA_DIST = \
src/resid/AUTHORS \
src/resid/ChangeLog \
src/resid/COPYING \
src/resid/configure.in \
src/resid/INSTALL \
src/resid/Makefile.am \
src/resid/NEWS \
src/resid/README \
src/resid/README.VICE \
src/resid/THANKS \
src/resid/TODO \
src/perfect6581/README \
$(noinst_DATA) \
$(noinst_SCRIPTS)

#=========================================================
# resid

resid_SOURCES = \
src/resid/dac.h \
src/resid/sid.h \
src/resid/voice.h \
src/resid/wave.h \
src/resid/envelope.h \
src/resid/filter.h \
src/resid/extfilt.h \
src/resid/pot.h \
src/resid/spline.h \
src/resid/dac.cc \
src/resid/sid.cc \
src/resid/voice.cc \
src/resid/wave.cc \
src/resid/envelope.cc \
src/resid/filter.cc \
src/resid/extfilt.cc \
src/resid/pot.cc \
src/resid/resid-config.h \
src/resid/version.cc \
$(noinst_DATA:.dat=.h)

noinst_DATA = \
src/resid/wave6581_PST.dat \
src/resid/wave6581_PS_.dat \
src/resid/wave6581_P_T.dat \
src/resid/wave6581__ST.dat \
src/resid/wave8580_PST.dat \
src/resid/wave8580_PS_.dat \
src/resid/wave8580_P_T.dat \
src/resid/wave8580__ST.dat

noinst_SCRIPTS = src/resid/samp2src.pl

.dat.h:
	$(PERL) $(srcdir)/src/resid/samp2src.pl $* $< $@

#=========================================================
# perfect6581

perfect6581_SOURCES = \
src/perfect6581/netlist_6581.h \
src/perfect6581/netlist_sim.c \
src/perfect6581/netlist_sim.h \
src/perfect6581/perfect6581.c \
src/perfect6581/perfect6581.h \
src/perfect6581/types.h

#=========================================================

bin_PROGRAMS = \
src/testresid

src_testresid_SOURCES = \
$(resid_SOURCES) \
$(perfect6581_SOURCES) \
src/test.cpp

