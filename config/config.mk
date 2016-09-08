# Configuration file for FIA-NET cpp-commons

export FIANET_COMMONS_CONFIG_DIR=$(FIANET_COMMONS_DIR)/config

# architecture info
include $(FIANET_COMMONS_CONFIG_DIR)/arch/x86.mk

# googletest
include $(FIANET_COMMONS_CONFIG_DIR)/gtest/gtest-usr-local.mk
