.PHONY: all clean

INC     :=   -I"./include"
CFLAGS	:= -O3 -Wall -std=gnu11 $(INC)

SRCS    :=$(shell find . -name '*.c')
OBJS    :=$(SRCS:%.c=%.o)
BUILDDIR:= build
OBJDIR  := $(BUILDDIR)/obj


all: mktree $(OBJS) mklib

mktree:
	mkdir -p $(OBJDIR)

%.o: %.c
	if [ ! -e $(OBJDIR)/$(notdir $@) ]; then gcc $(CFLAGS) -c -o $(OBJDIR)/$(notdir $@) $<; fi

mklib:
	ar -rcs $(BUILDDIR)/libtinycore.a $(OBJDIR)/*.o

clean:
	rm -rf $(BUILDDIR)
