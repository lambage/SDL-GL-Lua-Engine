## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
 
## Define SDL-GL-Lua-Engine library
lib_LTLIBRARIES = libSGLE.la 
libSGLE_la_SOURCES = src/SceneManager/GLObject.cpp \
	src/SceneManager/GLPanel.cpp \
	src/SceneManager/SceneManager.cpp \
	src/SceneManager/ShaderManager.cpp \
	src/Util/Log.cpp
	

## Define sample programs
bin_PROGRAMS = sample1
 
## Define the list of source files for the "hello" target. The file extension
## .cc is recognized by Automake, and causes it to produce rules which invoke
## the C++ compiler to produce an object file (.o) from each source file. The
## header files (.h) do not result in object files by themselves, but will be
## included in distribution archives of the project.
AM_CPPFLAGS = -Isrc
sample1_SOURCES = samples/sample1.cpp
sample1_LDADD =  libSGLE.la 
sample1_LDADD += $(SDL2_LIBS) $(GLEW_LIBS)

## Define an independent executable script for inclusion in the distribution
## archive. It will not be installed on an end user's system, however.
dist_noinst_SCRIPTS = autogen.sh

