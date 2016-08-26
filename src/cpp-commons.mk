ifeq ($(FIANET_COMMONS_DIR),)
  $(error "Please define FIANET_COMMONS_DIR")
endif

# Base directories for cpp-commons 
FIANET_COMMONS_SRCDIR = $(FIANET_COMMONS_DIR)/src
FIANET_COMMONS_INCDIR = $(FIANET_COMMONS_DIR)/include
FIANET_COMMONS_LIBDIR = $(FIANET_COMMONS_DIR)/lib

# fianet-core
LIBFIANETCORE_SRCDIR = $(FIANET_COMMONS_SRCDIR)/fianet-core
LIBFIANETCORE_INCDIR = $(FIANET_COMMONS_INCDIR)
LIBFIANETCORE_LIBDIR = $(FIANET_COMMONS_LIBDIR)
LIBFIANETCORE        = $(LIBFIANET3_LIBDIR)/libfianet-core.a
