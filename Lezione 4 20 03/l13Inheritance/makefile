CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
OBJS = $(ODIR)/InheritanceTest.o \
        $(ODIR)/Arma.o \
        $(ODIR)/Personaggio.o \
		$(ODIR)/Guerriero.o \
		$(ODIR)/Ladro.o \
		$(ODIR)/Mago.o \
		$(ODIR)/Elementalista.o \
		$(ODIR)/Assassino.o
        
LINK_TARGET = InheritanceTest.exe

all: $(LINK_TARGET)
	echo All done

$(LINK_TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@

InheritanceTest.o : Personaggio.h Arma.h Guerriero.h Ladro.h Mago.h Elementalista.h
Personaggio.o : Personaggio.h Arma.h
Arma.o : Arma.h
Guerriero.o : Guerriero.h Personaggio.h Arma.h
Ladro.o : Ladro.h Personaggio.h Arma.h
Mago.o : Mago.h Personaggio.h Arma.h
Elementalista.o : Elementalista.h Mago.h Personaggio.h Arma.h
Assassino.o : Assassino.h Ladro.h Personaggio.h Arma.h


    
    