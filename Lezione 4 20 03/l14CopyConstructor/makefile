CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
OBJS = $(ODIR)/CopyConstructorTest.o \
        $(ODIR)/Arma.o \
        $(ODIR)/Personaggio.o \
		$(ODIR)/Guerriero.o 
        
LINK_TARGET = CopyConstructorTest.exe

all: $(LINK_TARGET)
	echo All done

$(LINK_TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $^ -o $@

CopyConstructorTest.o : Personaggio.h Arma.h Guerriero.h 
Personaggio.o : Personaggio.h Arma.h
Arma.o : Arma.h
Guerriero.o : Guerriero.h Personaggio.h Arma.h


    
    