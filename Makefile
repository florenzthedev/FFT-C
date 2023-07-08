#  Copyright (c) 2023 Zachary Todd Edwards
#  MIT License

CC = gcc
LD = gcc
CFLAGS = -Wall -I$(HEDDIR) -fPIC -fcx-limited-range
LFLAGS = -shared -Wl,-soname,$(EXEC) $(CFLAGS)

HEDDIR = .
SRCDIR = .
OBJDIR = ./obj

EXEC = libfft.so

LIBS = -lm -lc

_DEPS = fft.h
DEPS = $(patsubst %,$(HEDDIR)/%,$(_DEPS))

_OBJ = fft.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(EXEC): $(OBJ)
	$(LD) -o $@ $(OBJ) $(LIBS) $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS) | $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR):
	mkdir -p $@

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o core $(EXEC)
