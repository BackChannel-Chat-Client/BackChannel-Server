INCDIR=include
LIBDIR=lib
OBJDIR=build
SRCDIR=src
LIBS=-lcrypto -lssl -lpthread

CC=gcc
CFLAGS=-Wall -I$(INCDIR) -L$(LIBDIR) $(LIBS)

CFILES = $(shell find ./src -name '*.c')
OBJ = $(CFILES:.c=.o)
DEPS = $(shell find ./include -name '*.h')

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

backchannel-server: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

all: clean backchannel-server
	echo "[+] Build complete"

clean:
	rm -rf $(OBJ)
