CC = g++
DEBUG = -g -std=c++11 
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj

TMPLTOBJ = $(ODIR)/Templates2.o          
        
LINK_TARGET =  Templates2.exe

all: $(LINK_TARGET)
	echo All done

Templates2.exe : $(TMPLTOBJ)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@

Templates2.cpp : MyPair.h


    
    