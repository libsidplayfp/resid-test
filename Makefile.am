
ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = foreign subdir-objects


if MINGW32
  W32_CPPFLAGS = -DWIN32_LEAN_AND_MEAN
endif


AM_CPPFLAGS = -I $(top_srcdir)/src \
-I $(top_builddir)/src/resid \
-I $(top_builddir)/src/residfp \
${W32_CPPFLAGS}

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
src/residfp/AUTHORS \
src/residfp/COPYING \
src/residfp/README \
src/perfect6581/README \
$(noinst_DATA) \
$(noinst_SCRIPTS)

#=========================================================
# resid

src_libresid_a_CPPFLAGS = \
-DVERSION=\"1.0-pre2\" \
$(AM_CPPFLAGS)

src_libresid_a_SOURCES = \
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

BUILT_SOURCES = $(noinst_DATA:.dat=.h)

#=========================================================
# residfp

src_libresidfp_a_CPPFLAGS = \
$(AM_CPPFLAGS)

src_libresidfp_a_SOURCES = \
src/residfp/array.h \
src/residfp/Dac.cpp \
src/residfp/Dac.h \
src/residfp/EnvelopeGenerator.cpp \
src/residfp/EnvelopeGenerator.h \
src/residfp/ExternalFilter.cpp \
src/residfp/ExternalFilter.h \
src/residfp/Filter.cpp \
src/residfp/Filter.h \
src/residfp/Filter6581.cpp \
src/residfp/Filter6581.h \
src/residfp/Filter8580.cpp \
src/residfp/Filter8580.h \
src/residfp/FilterModelConfig.cpp \
src/residfp/FilterModelConfig.h \
src/residfp/FilterModelConfig8580.cpp \
src/residfp/FilterModelConfig8580.h \
src/residfp/Integrator.cpp \
src/residfp/Integrator.h \
src/residfp/Integrator8580.cpp \
src/residfp/Integrator8580.h \
src/residfp/OpAmp.cpp \
src/residfp/OpAmp.h \
src/residfp/Potentiometer.h \
src/residfp/SID.cpp \
src/residfp/SID.h \
src/residfp/Spline.cpp \
src/residfp/Spline.h \
src/residfp/version.cc \
src/residfp/Voice.h \
src/residfp/WaveformCalculator.cpp \
src/residfp/WaveformCalculator.h \
src/residfp/WaveformGenerator.cpp \
src/residfp/WaveformGenerator.h \
src/residfp/resample/Resampler.h \
src/residfp/resample/SincResampler.cpp \
src/residfp/resample/SincResampler.h \
src/residfp/resample/TwoPassSincResampler.h \
src/residfp/resample/ZeroOrderResampler.h

#=========================================================
# perfect6581

src_libperfect6581_a_CFLAGS = -std=c99

if USE_MOS8580
src_libperfect6581_a_CPPFLAGS = -DMOS8580
endif

src_libperfect6581_a_SOURCES = \
src/perfect6581/netlist_6581.h \
src/perfect6581/netlist_sim.c \
src/perfect6581/netlist_sim.h \
src/perfect6581/perfect6581.c \
src/perfect6581/perfect6581.h \
src/perfect6581/types.h

#=========================================================

noinst_LIBRARIES = \
src/libresid.a \
src/libresidfp.a \
src/libperfect6581.a

bin_PROGRAMS = \
src/testresid

src_testresid_SOURCES = \
src/perfect6581Wrapper.cpp \
src/perfect6581Wrapper.h \
src/residfpWrapper.cpp \
src/residfpWrapper.h \
src/residWrapper.cpp \
src/residWrapper.h \
src/test.cpp \
src/testBench.cpp \
src/testBench.h \
src/testParser.cpp \
src/testParser.h \
src/wrapper.h

src_testresid_CPPFLAGS =  \
@debug_flags@ \
$(AM_CPPFLAGS)

src_testresid_LDADD = \
src/libresid.a \
src/libresidfp.a \
src/libperfect6581.a
