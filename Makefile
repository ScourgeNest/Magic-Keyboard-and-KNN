# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -Wshadow -Wpedantic -std=c99 -O0 -g

# define targets
TARGETS=kNN mk

#define object-files
OBJ=mk.o kNN.o

build: $(TARGETS)

mk: mk.o
	$(CC) $(CFLAGS) $^ -o $@ trie.c

kNN: kNN.o
	$(CC) $(CFLAGS) $^ -o $@ BST.c

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

pack:
	zip -FSr 315CA_NiculiciMihai-Daniel_Tema3.zip README.md Makefile *.c *.h

clean:
	rm -f $(TARGETS) $(OBJ)

.PHONY: pack clean
