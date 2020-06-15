CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
STRINGOBJS = $(ODIR)/StringTest.o 
        
LINK_TARGET = StringTest.exe 

all: $(LINK_TARGET)
	echo All done

StringTest.exe : $(STRINGOBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@
	
    