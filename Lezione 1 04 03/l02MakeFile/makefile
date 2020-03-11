CC = g++
DEBUG = -g -std=c++11
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
OBJS = $(ODIR)/HelloWorld.o

all: helloworld run 

helloworld : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o helloworld

$(ODIR)/HelloWorld.o : HelloWorld.cpp
	$(CC) $(CFLAGS) HelloWorld.cpp -o $(ODIR)/HelloWorld.o

run:
	./helloworld
