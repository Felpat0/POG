CC = g++
DEBUG = -g -std=c++11
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
OBJS = scopetest.o
LINK_TARGET = scopetest.exe

all: $(LINK_TARGET) 

$(LINK_TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@

