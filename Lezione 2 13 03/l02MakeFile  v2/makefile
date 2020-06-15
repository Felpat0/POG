CC = g++
DEBUG = -g -std=c++11
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
ODIR = obj/

# possiamo rendere le cose ancora piu' generiche sfruttando alcuni simboli speciali e le variabili
# creo una variabile con i file header (sara' piu' chiaro in futuro)
DEPS = functions.h


exec: $(ODIR)main.o $(ODIR)func1.o $(ODIR)func2.o
	$(CC) $(LFLAGS) $(ODIR)main.o $(ODIR)func1.o $(ODIR)func2.o -o test2

# definisco una regola che ha effetto su tutti i file di un certo tipo
# % e' il simbolo per farlo
# la seguente regola vale per tutti i file .o (nella cartella obj) che dipendono da un file .cpp CON LO STESSO NOME
$(ODIR)%.o : %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<
# -c 
# -o come al solito e' il parametro per specificare l'output
# $@ e' cio' che e' scritto a sinistra dei :   ovvero il nome del file che ci interessa compilare
# $< e' il primo elemento dopo i : ovvero il nome del file cpp da cui partire

clean:
	del /s /q *.o test2