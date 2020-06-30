# Project Name
TARGET = Vowelizer

# Sources
CPP_SOURCES = Vowelizer.cpp

# Library Locations
LIBDAISY_DIR = ../../libdaisy
DAISYSP_DIR = ../../DaisySP

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

