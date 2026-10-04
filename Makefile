TARGET = psp_gfx

SOURCES_C := $(wildcard *.c) $(wildcard src/*.c)

OBJS := $(SOURCES_C:.c=.o)

CFLAGS = -O2 -G0 -Wall -Iinclude
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSP GFX

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

.PHONY: clean_src

clean_src:
	rm -f src/*.o

clean: clean_src