dnl Copyright (c) 2005, Eric Crahen
dnl
dnl Permission is hereby granted, free of charge, to any person obtaining a copy
dnl of this software and associated documentation files (the "Software"), to deal
dnl in the Software without restriction, including without limitation the rights
dnl to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
dnl copies of the Software, and to permit persons to whom the Software is furnished
dnl to do so, subject to the following conditions:
dnl 
dnl The above copyright notice and this permission notice shall be included in all
dnl copies or substantial portions of the Software.
dnl 
dnl THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
dnl IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
dnl FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
dnl AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
dnl CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

AC_REVISION($Revision: 1.14 $ZT_VERSION $)

AC_INIT
AC_CONFIG_SRCDIR([README])
AC_COPYRIGHT([Eric Crahen, 2000-2002])

AC_CANONICAL_HOST
AC_CANONICAL_TARGET

ZT_MAJOR_VERSION=2
ZT_MINOR_VERSION=3
ZT_MICRO_VERSION=2
ZT_INTERFACE_AGE=0
ZT_BINARY_AGE=0
ZT_VERSION=$ZT_MAJOR_VERSION.$ZT_MINOR_VERSION.${ZT_MICRO_VERSION}

AC_SUBST(ZT_MAJOR_VERSION)
AC_SUBST(ZT_MINOR_VERSION)
AC_SUBST(ZT_MICRO_VERSION)
AC_SUBST(ZT_INTERFACE_AGE)
AC_SUBST(ZT_BINARY_AGE)
AC_SUBST(ZT_VERSION)


dnl prepare version info
LT_RELEASE=$ZT_MAJOR_VERSION.$ZT_MINOR_VERSION
LT_CURRENT=`expr $ZT_MICRO_VERSION - $ZT_INTERFACE_AGE`
LT_REVISION=$ZT_INTERFACE_AGE
LT_AGE=`expr $ZT_BINARY_AGE - $ZT_INTERFACE_AGE`

AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)


AM_INIT_AUTOMAKE(ZThread, $ZT_VERSION)

AM_CONFIG_HEADER(src/config.h)
AM_ACLOCAL_INCLUDE(share)

dnl Check for support
AC_PROG_CXX

COMPILER_OPTIONS=""
LINKER_OPTIONS=""

dnl Check for pthreads support
AM_DETECT_PTHREAD
AM_WITH_DOXYGEN

AM_ENABLE_ATOMIC_LINUX
AM_ENABLE_ATOMIC_GCC
AM_DETECT_FTIME


dnl Setup compiler/linker options based on the target type
case "$target" in
*-*-mingw32*)
    dnl MingW32 should use native win32 threads
    ;;
*-apple-darwin*)
    dnl Use the Mac multiprocessing library
    LINKER_OPTIONS="-framework CoreServices"
    ;;
*)
    dnl Assume pthreads
    if test x"$PTHREAD_CFLAGS" != x; then
      COMPILER_OPTIONS="$PTHREAD_CFLAGS"
    fi
    if test x"$PTHREAD_LIBS" != x; then
      LINKER_OPTIONS="$PTHREAD_LIBS"
    fi
    ;;
esac

dnl Switch to C++ mode and check for needed C++ headers
AC_LANG_PUSH([C++])

dnl Configure the compiling options
case "$CXX" in
  *cl.exe)   # Microsoft Visual Studio
  CXXFLAGS="/nologo /MT /W3 /GX /O2 /YX /FD /c"
  CXXFLAGS="$CXXFLAGS /D \"_MBCS\" /D \"_LIB" /D \"WIN32\"
  ;;
  *)         # GNU
  CXXFLAGS="$CXXFLAGS -Wall"
  ;;
esac

dnl Header checks
AC_HEADER_STDC
AC_CHECK_HEADERS(errno.h)


dnl Check for debug-mode
AC_ARG_ENABLE(debug,
[  --enable-debug          Enable debug symbols [default=no]],

[
dnl Enable debug info
case "$CXX" in
  *cl.exe)
    ;;
  *)
    CXXFLAGS="$CXXFLAGS -g"
esac
],[
dnl Disable debug info
case "$CXX" in
  *cl.exe)
    CXXFLAGS="$CXXFLAGS /D NDEBUG"
    ;;
  *)

    CXXFLAGS="$CXXFLAGS -DNDEBUG"
esac
])

dnl Select implementation
AC_MSG_CHECKING(for target implementation)
ZT_TYPE="auto"

AC_ARG_ENABLE(win9x,
[  --enable-win9x          Select WIN9X implementation [default=no]],
[
  if test $ZT_TYPE != auto; then
     AC_MSG_ERROR(Select one implementation)
  fi
  ZT_TYPE="win9x"
  COMPILER_OPTIONS="$COMPILER_OPTIONS -DZT_WIN9X"
])

AC_ARG_ENABLE(win32,
[  --enable-win32          Select WIN32 implementation [default=autodetect]],
[
  if test $ZT_TYPE != auto; then
     AC_MSG_ERROR(Select one implementation)
  fi
  ZT_TYPE="win32"
  COMPILER_OPTIONS="$COMPILER_OPTIONS -DZT_WIN32"
])

AC_ARG_ENABLE(posix,
[  --enable-posix          Select POSIX implementation [default=autodetect]],
[
  if test $ZT_TYPE != auto; then
     AC_MSG_ERROR(Select one implementation)
  fi
  ZT_TYPE="posix"
  COMPILER_OPTIONS="$COMPILER_OPTIONS -DZT_POSIX"
])

AC_ARG_ENABLE(macos,
[  --enable-macos          Select MacOS implementation [default=autodetect]],
[
  if test $ZT_TYPE != auto; then
     AC_MSG_ERROR(Select one implementation)
  fi
  ZT_TYPE="macos"
  COMPILER_OPTIONS="$COMPILER_OPTIONS -DZT_MACOS"
])

AC_ARG_ENABLE(vanilla,
[  --enable-vanilla        Select vanilla implementation [default=autodetect]],
[
  COMPILER_OPTIONS="$COMPILER_OPTIONS -DZT_VANILLA"
])


if test $ZT_TYPE = auto; then
  ZT_TYPE="compile-time guess"
fi

AC_MSG_RESULT($ZT_TYPE)

dnl Configure targets
SUBDIRS="src"

dnl AC_ARG_ENABLE(examples,
dnl [  --enable-examples       Include examples in the project build. [default=yes]],,
dnl [
dnl  SUBDIRS="$SUBDIRS examples"
dnl ])

dnl Enable priorities
AC_ARG_ENABLE(priorities, [  --enable-priorities     Enable pthreads priorities [default=yes]], AC_DEFINE(ZTHREAD_DISABLE_PRIORITY,,[No OS priority support]))

dnl Disable IO interrupt w/ signal mechanism
AC_ARG_ENABLE(io-interrupts, [  --enable-interrupts  Enable interrupt hooks [default=yes]], AC_DEFINE(ZTHREAD_DISABLE_INTERRUPT,,[No interrupt() hooks]))

dnl Check for setsigjmp
AC_MSG_CHECKING(for sigsetjmp())
AC_TRY_LINK( [#include <setjmp.h>], [sigjmp_buf t; sigsetjmp(t, 0);],
[AC_MSG_RESULT(yes)],
[AC_MSG_RESULT(no)
 AC_DEFINE(ZTHREAD_DISABLE_INTERRUPT,,[No interrupt() hooks])
])

dnl Check for beginthreadex
AC_MSG_CHECKING(for _beginthreadex())
AC_TRY_LINK( [#include <windows.h>], [_beginthreadex((void*)0, 0, 0, (void*)0, 0, (void*)0);],
[
 AC_MSG_RESULT(yes)
 AC_DEFINE(HAVE_BEGINTHREADEX,,[_beginthreadex()])
], [AC_MSG_RESULT(no)])

dnl Configure the final compiler & linker options
COMPILER_OPTIONS="$COMPILER_OPTIONS $CXXFLAGS"
LINKER_OPTIONS="$LINKER_OPTIONS $LDFLAGS"

dnl Configured flags for compiling ZThreads
AC_SUBST(LINKER_OPTIONS)
AC_SUBST(COMPILER_OPTIONS)

dnl Extra variables users can customize
AC_SUBST(EXTRA_LINKER_OPTIONS)
AC_SUBST(EXTRA_COMPILER_OPTIONS)

AM_PROG_LIBTOOL

AC_SUBST(SUBDIRS)


AC_CONFIG_FILES([Makefile src/Makefile share/zthread-config share/zthread.spec])
AC_OUTPUT
