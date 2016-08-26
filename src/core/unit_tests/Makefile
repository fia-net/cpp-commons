###############################################################
## FIA-NET C++ commons
## (c) Fia-Net 2008 - 2016
################################################################

ifeq ($(FIANET_MK),)
  $(error "FIANET_MK is undefined.")
endif
include $(FIANET_MK)

################################################################
## setup gtest flags
################################################################
MY_INCDIRS+=$(GTEST_INCDIR) ..
MY_LIBDIRS+=$(GTEST_LIBDIR) ..
MY_LIBFLAGS+=$(GTEST_LIBFLAGS)

# disable some annoying GCC warnings
CXXFLAGS:=$(filter-out -Weffc++,$(CXXFLAGS))

################################################################
## Build dependancies
################################################################
COMMON_LIBS = ../libfianet-core.a $(LIBGTEST)

TEST_EXE = test
TEST_OBJ = String_toInt.o String_toFloat.o String_substr.o \
	String_comparisons.o  String_trim.o \
	XString_trim.o XString_append.o \
	XString_misc.o \
	StringTokenizer_tests.o \
	String_indexof.o \
	String_memfind.o \
	main.o
TEST_DEP_LIB = $(COMMON_LIBS)

################################################################
## General rules
################################################################
TARGETS = $(TEST_EXE)

all: $(TARGETS)

clean:
	$(RM) $(COMMON_CLEAN_FILES) $(TARGETS)

distclean: clean

################################################################
## Target construction rules
################################################################
$(TEST_EXE): $(TEST_OBJ) $(TEST_DEP_LIB)
	$(BUILD_CPP_EXE)
