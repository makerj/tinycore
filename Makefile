.PHONY: all clean

CFLAGS	= -O3 -Wall -std=gnu11 -c $(INC)

SRCS    =$(shell find . -name '*.c')
OBJS    =$(SRCS:%.c=%.o)
BUILDDIR = build
OBJDIR  = $(BUILDDIR)/obj

INC     =   -I"./include"

all: mktree $(OBJS) mklib

mktree:
	mkdir -p $(OBJDIR)

%.o: %.c
	@echo $(OBJS)
	gcc $(CFLAGS) -c -o $(OBJDIR)/$(notdir $@) $<

mklib:
	ar -rcs $(BUILDDIR)/libtinycore.a $(OBJDIR)/*.o

clean:
	rm -rf $(BUILDDIR)
