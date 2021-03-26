module_LTLIBRARIES			+= modules/regexp/libregexp-plugin.la

modules_regexp_libregexp_plugin_la_SOURCES	=	\
	modules/regexp/regexp-parser.c			\
	modules/regexp/regexp-parser.h			\
	modules/regexp/regexp-parser-grammar.y		\
	modules/regexp/regexp-parser-parser.c		\
	modules/regexp/regexp-parser-parser.h		\
	modules/regexp/regexp-parser-plugin.c

modules_regexp_libregexp_plugin_la_CPPFLAGS	=	\
	$(AM_CPPFLAGS)				\
	-I$(top_srcdir)/modules/regexp		\
	-I$(top_builddir)/modules/regexp
modules_regexp_libregexp_plugin_la_LIBADD	=	\
	$(MODULE_DEPS_LIBS)
modules_regexp_libregexp_plugin_la_LDFLAGS	=	\
	$(MODULE_LDFLAGS)
modules_regexp_libregexp_plugin_la_DEPENDENCIES	=	\
	$(MODULE_DEPS_LIBS)

modules/regexp modules/regexp mod-regexp: modules/regexp/libregexp-plugin.la
.PHONY: modules/regexp/ mod-regexp

BUILT_SOURCES       +=      \
  modules/regexp/regexp-parser-grammar.y       \
  modules/regexp/regexp-parser-grammar.c       \
  modules/regexp/regexp-parser-grammar.h

EXTRA_DIST        +=      \
  modules/regexp/regexp-parser-grammar.ym	\
  modules/regexp/CMakeLists.txt

include modules/regexp/tests/Makefile.am