CC=gcc
CLFAGS=-g -Wall
INCLUDE=./include
VPATH=./src

all:set_main list_main stack_main HashKit_main

list_main:list.o list_main.o

set_main:set.o set_main.o

stack_main:stack.o stack_main.o

HashKit_main:HashKit_main.o libHashKit.a

libHashKit.a:HashKit.o
	ar rv $@ $<

%.o:%.c
	$(CC) -I$(INCLUDE) -c $(CFLAGS) $< -I$(INCLUDE) -o $@

clean:
	rm ./*.o set_main list_main stack_main HashKit_main *.a *~ -r
	
