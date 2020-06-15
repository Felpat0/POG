CC = g++
DEBUG = -g -std=c++11 -static-libstdc++
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj
RPDXMLLIB = lib/rapidxml/rapidxml.hpp lib/rapidxml/rapidxml_iterators.hpp \
            lib/rapidxml/rapidxml_utils.hpp lib/rapidxml/rapidxml_print.hpp 

RPDXML = $(ODIR)/RapidXMLTest.o
       
        
LINK_TARGET = RapidXMLTest.exe 

all: $(LINK_TARGET)
	echo All done

RapidXMLTest.exe : $(RPDXML)
	$(CC) $(LFLAGS) $^ -o $@
	
$(ODIR)/%.o : %.cpp 
	$(CC) $(CFLAGS) $(SOILLIB) $< -o $@


RapidXMLTest.o : $(RPDXMLLIB) 


    
    