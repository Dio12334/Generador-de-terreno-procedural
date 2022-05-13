objects = main.o world.o functions.o
CFLAGS = -Wall -O2 
debugflags = -g
execname = a.out

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += $(debugflags)
endif

all: build

debug: clean build

build: $(objects)
	g++ $(CFLAGS) -o $(execname) $(objects) 

%.o : %.cpp
	g++ -c $(CFLAGS) $< -o $@

.PHONY: clean cleanall
clean:
	rm -f $(objects)

cleanall: clean
	rm -f $(execname)
