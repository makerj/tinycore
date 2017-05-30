.PHONY: all clean
#VPATH := add:multiple:paths:like:this
VPATH := src

BUILDDIR:= build
OBJDIR  := $(BUILDDIR)/obj

INC     := -I"./include"
CFLAGS	:= -O3 -Wall -std=gnu11 $(INC)

SRCS    := $(notdir $(shell find . -name '*.c'))
OBJS    := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

LIBRARY := $(BUILDDIR)/libtinycore.a

all: mktree $(LIBRARY)

mktree:
	@if [ ! -e $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi

$(OBJDIR)/%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

$(LIBRARY): $(OBJS)
	ar -rcs $@ $^

clean:
	rm -rf $(BUILDDIR)

