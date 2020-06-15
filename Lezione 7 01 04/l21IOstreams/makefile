CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj

IOSTREAMS = $(ODIR)/IOstreamsTest.o
USERDFND = $(ODIR)/UserDefinedIOTest.o          
        
LINK_TARGET = IOstreamsTest.exe UserDefinedIOTest.exe

all: $(LINK_TARGET)
	echo All done

IOstreamsTest.exe : $(IOSTREAMS)
	$(CC) $(LFLAGS) $^ -o $@
	
UserDefinedIOTest.exe : $(USERDFND)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@

UserDefinedIOTest.o : Personaggio.h Guerriero.h Arma.h
IOstreamsTest.o : Personaggio.h Guerriero.h Arma.h
Personaggio.o : Personaggio.h Arma.h
Guerriero.o : Guerriero.h Personaggio.h Arma.h
Arma.o : Arma.h



    
    