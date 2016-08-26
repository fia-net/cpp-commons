#############################################################
# fia-net.mk
#
# This file contains all the rules needed to compile our
# C++ commons libraries.
#
#############################################################

ifeq ($(FIANET_COMMONS_DIR),)
  $(error "Missing FIANET_COMMONS_DIR environment variable.")
endif

include $(FIANET_COMMONS_DIR)/config/config.mk
ifeq ($(ARCH_CFLAGS),)
  $(error "Please check the file $(FIANET_COMMONS_DIR)/config/config.mk")
endif

include $(FIANET_COMMONS_DIR)/src/cpp-commons.mk
ifeq ($(FIANET_COMMONS_INCDIR),)
  $(error "Please check the file $(FIANET_COMMONS_DIR)/src/cpp-commons.mk")
endif

###########################
# Common for all Makefiles
###########################

.SUFFIXES: .cpp .cp .c .o .h .a .so
.PHONY: all clean distclean install rev_info

COMMON_CLEAN_FILES = *.a *.o core *~ *.bak *.old .pure.*

#####################
## Compilation flags
#####################
OPTIM_CFLAGS ?= -O0 -g

# Repertoires ou on va chercher les .h, par defaut:
GEN_INCDIRS += $(FIANET_GLOBAL_INCDIR) $(EXT_GLOBAL_INCDIR) $(SYBASE_INCDIR)

# Liste des repertoires ou on va chercher les libs
# pour generer les programmes, par defaut:
GEN_LIBDIRS += $(FIANET_GLOBAL_LIBDIR) $(EXT_GLOBAL_LIBDIR) $(SYBASE_LIBDIR)

# Parametres par defaut passes a GCC pour la compilation C
GEN_CFLAGS = $(OPTIM_CFLAGS) $(ARCH_CFLAGS) -Wall -Wextra -D_REENTRANT $(ARCH) 

# Parametres par defaut passes a GCC pour la compilation C++ : la meme chose qu'en C et des trucs en plus.
GEN_CXXFLAGS = $(GEN_CFLAGS) -Weffc++

# Parametres par defaut passes a LD
GEN_LDFLAGS = $(ARCH_LDFLAGS)

# Libs systemes (ex: -lrt)
GEN_LIBFLAGS = $(ARCH_LIBFLAGS)

LDFLAGS = $(addprefix -L, $(MY_LIBDIRS) $(GEN_LIBDIRS)) $(MY_LDFLAGS) $(GEN_LDFLAGS)
CFLAGS = $(GEN_CFLAGS) $(addprefix -I, . $(MY_INCDIRS) $(GEN_INCDIRS)) $(MY_CFLAGS) $(ADD_DEFINE) -fexceptions
CXXFLAGS = $(GEN_CXXFLAGS) $(addprefix -I, . $(MY_INCDIRS) $(GEN_INCDIRS)) $(MY_CXXFLAGS) $(ADD_DEFINE)
ARFLAGS = crus

##########################################
## Helpers for linking binaries and libs.
##########################################

# AUTO_LIBS:
# Transforms "libA.a libB.a libC.so" into "-lA -lB -lC"
define AUTO_LIBS
$(addprefix -l, $(patsubst lib%,%, $(basename $(notdir $(filter %.a,$^) $(filter %.so,$^))))) 
endef

# AUTO_OBJS: extract the .o files from a list of dependencies.
define AUTO_OBJS
$(filter %.o,$^)
endef

# BUILD_C_EXE:
# Links a binary from objects and libs with GCC (for C sources):
#
# $(CCLD) -o mon_exe mon_obj1.o mon_obj2.o $(LDFLAGS) -lmalib1 -lmalib2
define BUILD_C_EXE
$(CCLD) -o $@ $(AUTO_OBJS) $(LDFLAGS) $(MY_LIBS) $(AUTO_LIBS) $(AUTO_SYBLIBS) $(MY_LIBFLAGS) $(GEN_LIBFLAGS)
endef


# BUILD_CPP_EXE:
# Links a binary from objects and libs with GCC (for C++)
define BUILD_CPP_EXE
$(CCLD) -o $@ $(AUTO_OBJS) $(LDFLAGS) $(MY_LIBS) $(AUTO_LIBS) $(AUTO_SYBLIBS) $(MY_LIBFLAGS) $(GEN_LIBFLAGS) -lstdc++
endef

# BUILD_STATIC_LIB:
define BUILD_STATIC_LIB
$(AR) $(ARFLAGS) $@ $(AUTO_OBJS) 
endef

# BUILD_SHARED_LIB:
define BUILD_SHARED_LIB
$(CCLD) -shared -Wl,-soname,$@ -o $@ $(AUTO_OBJS)
endef

#####################
## Compilation rules
#####################
%.o: %.cc 
	$(CC) $(CXXFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

%.c: %.cp
	$(PROC) $(PROCFLAGS) -O$@ $<

