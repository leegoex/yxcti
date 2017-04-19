plug_in_name = cc_ts

SEMSPATH ?= ../../../..
COREPATH ?= $(SEMSPATH)/core
sbc_app_path = $(SEMSPATH)/apps/sbc
dsm_app_path = $(SEMSPATH)/apps/dsm

module_ldflags = 
module_cflags  = -DMOD_NAME=\"$(plug_in_name)\" -I$(sbc_app_path) -I$(dsm_app_path)

SUBDIRS := $(shell find . -maxdepth 1 -type d)
SUBDIRS := $(basename $(patsubst ./%,%,$(SUBDIRS)))
SUBDIRS := $(filter-out $(exclude_dirs),$(SUBDIRS))

.PHONY: all
all:
	@for r in $(SUBDIRS) ; do \
		$(MAKE) -C $$r; \
	done

.PHONY: cleansub
cleansub:
	@for r in $(SUBDIRS) ; do \
		$(MAKE) -C $$r clean; \
	done

include $(COREPATH)/plug-in/Makefile.app_module
