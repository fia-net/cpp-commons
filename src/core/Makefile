###############################################################
## FIA-NET C++ commons
## (c) Fia-Net 2008 - 2016
################################################################

ifeq ($(FIANET_MK),)
  $(error "FIANET_MK is undefined.")
endif
include $(FIANET_MK)

################################################################
## Destination folders
################################################################
HEADERS_INSTALLDIR = $(FIANET_COMMONS_INCDIR)
LIBS_INSTALLDIR = $(FIANET_COMMONS_LIBDIR)

################################################################
## Build dependencies
################################################################
FIANET_CORE_LIB	    = libfianet-core.a
FIANET_CORE_LIB_OBJ = Exception.o String.o XString.o StringTokenizer.o
FIANET_CORE_LIB_H   = Exception.h String.h XString.h StringTokenizer.h \
                      fianet-core.h

################################################################
## General rules
################################################################
TARGETS = $(FIANET_CORE_LIB)
HEADERS = $(FIANET_CORE_LIB_H)

all: $(TARGETS) install

install: $(TARGETS)
	$(INSTALL) $(HEADERS) $(HEADERS_INSTALLDIR)
	$(INSTALL) $(TARGETS) $(LIBS_INSTALLDIR)

clean:
	$(RM) $(COMMON_CLEAN_FILES)
	@if [ -d unit_tests ] ; then cd unit_tests && $(MAKE) clean ; fi

distclean: clean
	@for f in $(HEADERS); do $(RM) $(HEADERS_INSTALLDIR)/$$f ; done
	@if [ -d unit_tests ] ; then cd unit_tests && $(MAKE) distclean ; fi

tests: install
	@if [ -d unit_tests ] ; then cd unit_tests && $(MAKE) all ; fi

################################################################
## Target construction rules
################################################################
$(FIANET_CORE_LIB): $(FIANET_CORE_LIB_OBJ) $(FIANET_CORE_LIB_H)
	$(BUILD_STATIC_LIB)
