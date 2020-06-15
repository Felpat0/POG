CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
FPTROBJ = $(ODIR)/FunctionPointers.o
FUNCTOROBJ = $(ODIR)/Functors.o   
        
LINK_TARGET = FunctionPointers.exe Functors.exe 

all: $(LINK_TARGET)
	echo All done

FunctionPointers.exe : $(FPTROBJ)
	$(CC) $(LFLAGS) $^ -o $@

Functors.exe : $(FUNCTOROBJ)
	$(CC) $(LFLAGS) $^ -o $@


$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@





    
    