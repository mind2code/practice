CC=gcc
CFLAGS=-g -Wall
CPPFLAGS= -I include
VPATH=src include

all:set_main list_main stack_main HashKit_main

list_main:list.o list_main.o

set_main:set.o set_main.o

stack_main:stack.o stack_main.o

HashKit_main:HashKit_main.o libHashKit.a(HashKit.o)

libHashKit.a(HashKit.o):HashKit.o

clean:
	rm ./*.o set_main list_main stack_main HashKit_main *.a *~ -r -f
