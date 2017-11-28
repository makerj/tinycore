.PHONY: all clean
#VPATH := add:multiple:paths:like:this

BUILDDIR:= build
OBJDIR  := $(BUILDDIR)/obj
$(shell mkdir -p $(OBJDIR))

CFLAGS	:= -O3 -Wall -std=gnu11

SRCS    := $(notdir $(shell find . -name '*.c'))
OBJS    := $(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))

LIBRARY := $(BUILDDIR)/libtinycore.a

all: $(LIBRARY)

$(OBJDIR)/%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

$(LIBRARY): $(OBJS)
	ar -rcs $@ $^

clean:
	rm -rf $(BUILDDIR)

