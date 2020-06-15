CC = g++
DEBUG = -g  
CFLAGS =  -c $(DEBUG)
LFLAGS =  $(DEBUG)
ODIR = obj
OBJS = $(ODIR)/CnstPtrRefsTest.o
LINK_TARGET = CnstPtrRefsTest.exe

all: $(LINK_TARGET) 

$(LINK_TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@
