objects = main.o world.o functions.o Display.o

CFLAGS = -Wall -O2 
LINKERFLAGS = -lSDL2
debugflags = -g
CC = g++
execname = a.out

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += $(debugflags)
endif

all: build

debug: clean build

build: $(objects)
	$(CC) $(CFLAGS) -o $(execname) $(objects) $(LINKERFLAGS)

%.o : %.cpp
	$(CC) -c $(CFLAGS) $(LINKERFLAGS) $< -o $@

.PHONY: clean cleanall
clean:
	rm -f $(objects)

cleanall: clean
	rm -f $(execname)


