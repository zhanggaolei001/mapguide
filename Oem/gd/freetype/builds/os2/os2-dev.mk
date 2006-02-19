#
# FreeType 2 configuration rules for OS/2 + GCC
#
#   Development version without optimizations.
#


# Copyright 1996-2000, 2003 by
# David Turner, Robert Wilhelm, and Werner Lemberg.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.


ifndef TOP_DIR
  TOP_DIR := .
endif

include $(TOP_DIR)/builds/os2/os2-def.mk
BUILD_DIR := $(TOP_DIR)/devel

include $(TOP_DIR)/builds/compiler/gcc-dev.mk

# include linking instructions
include $(TOP_DIR)/builds/link_dos.mk


# EOF
