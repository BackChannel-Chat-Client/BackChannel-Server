INCDIR=include
LIBDIR=lib
OBJDIR=build
SRCDIR=src
LIBS=-lcrypto -lssl

CC=gcc
CFLAGS=-Wall -I$(INCDIR) -L$(LIBDIR) $(LIBS)

CFILES = main.c
OBJ = $(CFILES:.c=.o)
DEPS = $(wildcard $(INCDIR)*.h)

%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

backchannel-server: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LIBS)

all: backchannel-server
	echo $(DEPS)
	echo "[+] Build complete"