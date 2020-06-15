CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
OBJS = $(ODIR)/ClassTest.o \
        $(ODIR)/Arma.o \
        $(ODIR)/Personaggio.o
        
LINK_TARGET = ClassTest.exe 

all: $(LINK_TARGET) ClassTestMP.exe 
	echo All done

ClassTestMP.exe : $(ODIR)/ClassTestMP.o
	$(CC) $(LFLAGS) $^ -o $@
    
$(LINK_TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@

ClassTest.o : Personaggio.h Arma.h
Personaggio.o : Personaggio.h Arma.h
Arma.o : Arma.h


    
    