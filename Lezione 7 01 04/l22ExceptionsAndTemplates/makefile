CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj

EXCPTOBJ = $(ODIR)/ExceptionsTest.o
TMPLTOBJ = $(ODIR)/Templates.o          
        
LINK_TARGET = ExceptionsTest.exe Templates.exe

all: $(LINK_TARGET)
	echo All done

ExceptionsTest.exe : $(EXCPTOBJ)
	$(CC) $(LFLAGS) $^ -o $@
	
Templates.exe : $(TMPLTOBJ)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@




    
    