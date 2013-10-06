#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(bazar, 1.3.1, julien.pilet@epfl.ch)
AM_INIT_AUTOMAKE

AM_CONFIG_HEADER([config.h])


CXXFLAGS="$CXXFLAGS -std=c++0x"
                        
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB
LT_INIT


                     
# Checks for libraries.
AC_CHECK_LIB(GLEW, glewInit, have_glew=yes, have_glew=no, $GL_LIBS)

# Checks for header files.
AC_HEADER_STDC

AC_CHECK_LIB([GL], [glBegin], ,
    AC_CHECK_LIB([opengl32], [glBegin], , , GL_LIBS="-lopengl32")
    GL_LIBS="-lGL")
    
AC_CHECK_LIB([GLEW], [glBegin], ,
    AC_CHECK_LIB([glew32], [glBegin], , , GL_LIBS="-lglew32")
    GL_LIBS="-lGLEW")    

AC_CHECK_HEADER([GL/glew.h], [], have_glew=no)

if test "x$have_glew" != "xyes"; then
	AC_MSG_WARN([GL Extension Wrangler library not found.  Get it from http://glew.sourceforge.net])
fi
AC_SUBST(GL_LIBS)

if test "x$have_glew" = "xyes"; then
	HAVE_FULLGL="yes"
else
	HAVE_FULLGL="no"
fi
AM_CONDITIONAL(FULLGL, test x$HAVE_FULLGL=xyes)q1

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

SDL2_LIBS=
PKG_CHECK_MODULES(SDL2, sdl2, [AC_DEFINE([HAVE_SDL2],[1],[found sdl 2.x])], [AC_MSG_WARN("sdl 2.x not found")])
AC_SUBST(SDL2_CFLAGS)
AC_SUBST(SDL2_LIBS)


# Checks for library functions.
AC_CHECK_FUNCS([floor memset pow sqrt])
AC_CONFIG_FILES([
Makefile
])
AC_OUTPUT
AC_MSG_NOTICE([Build OpenGL example: $HAVE_FULLGL])