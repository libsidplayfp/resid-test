AC_INIT([resid-test], [0.1], [], [], [https://github.com/drfiemost/resid-test])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/test.cpp])
AC_CONFIG_HEADER([src/config.h])
AM_INIT_AUTOMAKE

AC_CANONICAL_HOST

AS_CASE([$host_os],
        [mingw*], [MINGW32=yes],
        [MINGW32=no]
)
AM_CONDITIONAL([MINGW32], [test "x$MINGW32" = "xyes"])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX

dnl Use C++ for tests.
AC_LANG([C++])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_SIZEOF([short])
AC_CHECK_SIZEOF([int])

AS_IF([test $ac_cv_sizeof_short -ne 2],
  [AC_MSG_ERROR([size of short must be 16 bit])]
)

AS_IF([test $ac_cv_sizeof_int -lt 4],
  [AC_MSG_ERROR([only 32 bit or better CPUs are supported])]
)

AS_IF([test "x${ac_cv_header_stdint_h}" != "xyes"],
  [AC_MSG_ERROR([Required header stdint.h not found])]
)

AC_MSG_CHECKING([for debugging])
AC_ARG_ENABLE(debug, [AS_HELP_STRING([--enable-debug], [compile for debugging @<:@no/yes/full, default=no@:>@])],
 [], [enable_debug=no])

AS_IF([test "x$enable_debug" = "xno"],
  [AC_MSG_RESULT([Build without debugging messages]); debug_flags=-DNDEBUG],
  [AS_IF([test "x$enable_debug" = "xyes"],
    [AC_MSG_RESULT([Build with debugging messages]); debug_flags=-DDEBUG=1],
    [AC_MSG_RESULT([Build with all debugging messages]); debug_flags=-DDEBUG=10]
  )]
)

AC_SUBST([debug_flags])


AC_ARG_ENABLE([inline],
  AS_HELP_STRING([--enable-inline],[enable inlining of functions [default=yes]])
)

AS_IF([test x"$enable_inline" != "xno"],
  [RESID_INLINE=inline; RESID_INLINING=1],
  [RESID_INLINE=""; RESID_INLINING=0]
)

AC_CACHE_CHECK([for working bool], ac_cv_cxx_bool,
[AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM([],
    [[bool flag;]])],
  [ac_cv_cxx_bool=yes],
  [ac_cv_cxx_bool=no])]
)

AS_IF([test "x$ac_cv_cxx_bool" = "xno"],
  [HAVE_BOOL=0],
  [HAVE_BOOL=1]
)

dnl Enable branch prediction hints.
AC_ARG_ENABLE([branch-hints],
  [AS_HELP_STRING([--enable-branch-hints],
    [enable static branch prediction hints [default=yes]])],
  [],
  [enable_branch_hints=yes]
)

AS_IF([test "$enable_branch_hints" != no],
  [RESID_BRANCH_HINTS=1],
  [RESID_BRANCH_HINTS=0]
)

AC_CACHE_CHECK([for log1p], [resid_cv_log1p],
  [AC_TRY_COMPILE([#include <math.h>], [ log1p(1); ],
    resid_cv_log1p=yes, resid_cv_log1p=no)])

AS_IF([test "$resid_cv_log1p" = no],
  [HAVE_LOG1P=0],
  [HAVE_LOG1P=1])


AC_CACHE_CHECK([for __builtin_expect], [resid_cv_builtin_expect],
  [AC_COMPILE_IFELSE([AC_LANG_SOURCE([int main() { __builtin_expect(0, 0); }])],
    [resid_cv_builtin_expect=yes], [resid_cv_builtin_expect=no])]
)

AS_IF([test "$resid_cv_builtin_expect" = no],
  [HAVE_BUILTIN_EXPECT=0],
  [HAVE_BUILTIN_EXPECT=1]
)

AC_SUBST(HAVE_BUILTIN_EXPECT)
AC_SUBST(RESID_BRANCH_HINTS)
AC_SUBST(HAVE_BOOL)
AC_SUBST(HAVE_LOG1P)
AC_SUBST(RESID_INLINING)
AC_SUBST(RESID_INLINE)


AC_CONFIG_FILES([
Makefile
src/resid/siddefs.h
])

AC_OUTPUT
