CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
OBJS = $(ODIR)/Arma.o \
        $(ODIR)/Personaggio.o \
		$(ODIR)/Guerriero.o 
LVVOBJS = $(ODIR)/ListVsVector.o $(OBJS)
MAPSOBJS = $(ODIR)/Maps.o         
        
LINK_TARGET = ListVsVector.exe Maps.exe

all: $(LINK_TARGET)
	echo All done

ListVsVector.exe : $(LVVOBJS)
	$(CC) $(LFLAGS) $^ -o $@
	
Maps.exe : $(MAPSOBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@

ListVsVector.o : Guerriero.h Personaggio.h  Arma.h
Personaggio.o : Personaggio.h Arma.h
Guerriero.o : Guerriero.h Personaggio.h Arma.h
Arma.o : Arma.h



    
    