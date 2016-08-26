# Fichier de configuration pour la compilation sur RHEL6 x86_64 compilation 32 bits, Sybase 15.7, Postgresql repo PGDG
#

export FIANET_COMMONS_CONFIG_DIR=$(FIANET_COMMONS_DIR)/config

# architecture info
include $(FIANET_COMMONS_CONFIG_DIR)/arch/x86.mk

# googletest
include $(FIANET_COMMONS_CONFIG_DIR)/gtest/gtest-usr-local.mk
