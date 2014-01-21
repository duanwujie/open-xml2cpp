#AM_CFLAGS = -std=c99 -Wall -Wextra -Werror -Wstrict-prototypes -Wredundant-decls -Wshadow -pedantic -fno-strict-aliasing -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600 -O2 -D_SVID_SOURCE

AM_CFLAGS = -Wunused-function -Wall

#if ENABLE_DEBUG_BUILD
#AM_CFLAGS += -g 
#else
#AM_CFLAGS += -DNDEBUG
#endif


INCLUDE = -I.
sbin_PROGRAMS = xml2cpp

XTC_PREFIX :=.
xml2cpp_SOURCES =     $(XTC_PREFIX)/tinyxml.cpp \
		      $(XTC_PREFIX)/tinyxmlparser.cpp \
		      $(XTC_PREFIX)/xml2cpp.cpp \
		      $(XTC_PREFIX)/tinyxmlerror.cpp \
		      $(XTC_PREFIX)/tinystr.cpp \
		      $(XTC_PREFIX)/XmlParser.cpp \
		      $(XTC_PREFIX)/CPPGen.cpp
