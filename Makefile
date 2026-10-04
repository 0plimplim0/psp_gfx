TARGET = PROJ_NAME

SOURCES_C := $(wildcard *.c) $(wildcard src/*.c)

OBJS := $(SOURCES_C:.c=.o)

INCDIRS = include

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = -lpspgum -lpspgu -lasound -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Project Name

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

.PHONY: clean

clean::
	rm -f src/*.o