# Config for core2 32 bits

AUTOCONF_BUILD = i686-pc-linux-gnu

ARCH_CFLAGS  = -m32 -march=core2
ARCH_LDFLAGS = -m32
ARCH_LIBFLAGS = -lrt

EXT_CFLAGS   = -m32 -march=core2
EXT_CXXFLAGS = -m32 -march=core2
EXT_LDFLAGS  = -m32

AR = ar
CC = gcc
CCLD = gcc

RM = rm -f
TAR = tar
INSTALL = install 

