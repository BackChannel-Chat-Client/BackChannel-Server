INCDIR=include
LIBDIR=lib
OBJDIR=build
SRCDIR=src
BINDIR=bin
LIBS=-lcrypto -lssl -lpthread

CC=gcc
CFLAGS=-Wall -Wno-unused-value -I$(INCDIR) -L$(LIBDIR) $(LIBS)

CFILES = $(shell find ./src -name '*.c')
OBJ = $(CFILES:.c=.o)
DEPS = $(shell find ./include -name '*.h')

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

backchannel-server: $(OBJ)
	mkdir -p bin
	$(CC) -o $(BINDIR)/$@ $(OBJ) $(CFLAGS)

all: clean backchannel-server
	echo "[+] Build complete"

clean:
	rm -rf $(OBJ)
