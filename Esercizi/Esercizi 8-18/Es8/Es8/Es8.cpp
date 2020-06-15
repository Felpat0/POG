/*Creare una classe Casa e la classica gerarchie di classi Persona, Studente, Docente.
-- Casa deve avere i campi numDiStanze, distanzaDalCentro.
-- Persona deve avere i campi char inizialeNome, inizialeCognome, e un puntatore di tipo
Casa.
- Il costruttore deve inizializzare le iniziali e settare nullptr il puntatore.
- Deve avere un metodo saluta() che stampa a schermo "Le mie iniziali sono" seguito dalle
due iniziali. Se il puntatore alla Casa non è nullo dovrà anche stampare " e abito in una casa
di " + numDiStanze + " a " + distanzaDalCentro + " metri dalla centro." . Questo metodo
dovrà supportare il binding dinamico in caso di override.
- Deve avere un metodo trasloca() che prende in input l'indirizzo di una Casa e lo assegna al
proprio puntatore.
- Implementare un distruttore. (cosa fare col puntatore Casa?)
-- Studente deve avere i campi matricola e un puntatore ad un array di interi.
- Il costruttore dovrà richiamare il costruttore della classe madre, inizializzare la matricola e
l'array con un array di 20 elementi con valori randomici tra 18 e 30.
- Deve avere un metodo calcolaMedia() che restituisce un intero rappresentante la sua media
- Deve effettuare l'override del metodo saluta() aggiungendo alla fine del risultato del metodo
della classe madre: " Sono uno studente con matricola " + matricola + " e i miei voti sono "
seguito da tutti i voti " con la media del " seguito dal risultato di calcolaMedia()
- Implementare un distruttore. (cosa fare con l'array?)
-- Docente deve avere i campi numInsegnamenti, numStudenti.
- Il costruttore dovrà richiamare il cosruttore della classe madre e inizializzare
numInsegnamenti e numStudenti.
- Deve fare l'override del metodo saluta() aggiugendo alla fine del risultato del metodo della
classe madre: "Sono un insegnante con " + numInsegnamenti+ " per un totale di " +
numStudenti + " studenti"
- Implementare un distruttore.
Nel main creare 4 Case e 7 Persone (tutti puntatori, no array).
Assegnare a ciascuna persona una Casa (quindi sì, più persone possono abitare nella stessa
casa, la casa non appartiene unicamente ad una persona) col metodo trasloca().
Le persone dovranno essere un po' studenti, un po' docenti e un po' persone generiche.
Scegliete voi se richiedere gli input da terminale.
Dopo averle create tutte, fate presentare tutte le persone.
Successivamente liberate la memoria prima di terminare il programma. */

#include<iostream>
#include <string>
#include<random>
#include <time.h>


class Casa {
public:
	int numDiStanze;
	int distanzaDalCentro;

	Casa(int s, int d) : numDiStanze(s), distanzaDalCentro(d) {}
};

class Persona {
public:
	char inizialeNome;
	char inizialeCognome;
	Casa* casa;

		Persona(char n, char c) : inizialeNome(n), inizialeCognome(c), casa(nullptr) {}

		virtual const void saluta() {
			std::cout << "Le mie iniziali sono " << inizialeNome << "." << inizialeCognome<<".";
			if (casa != nullptr)
				std::cout << "\nEd abito in una casa di " << casa->numDiStanze << " stanze che dista " << casa->distanzaDalCentro << " metri dal centro";;
		}

	void trasloca(Casa& nuova) {
			casa = &nuova;
		}

		~Persona() {
			inizialeCognome = ' ';
			inizialeNome = ' ';
			
			//delete casa;
		}
};
		
		

class Studente : public Persona {
	std::string matricola;
	int* voti[20];

public:
	Studente(std::string m, char n, char c) : Persona(n, c), matricola(m) {
		*voti = new int[20];
		srand(time(NULL));
		for (int i = 0; i != 20; i++) {
			*voti[i] = (rand() % 13) + 18;
		}

	}

	float calcolaMedia() {
		int m = 0;
		for (int i = 0; i != 20; i++) {
			m += *voti[i];
		}
		return ((float)m) / 20;
	}

	
	const void saluta() override{
		Persona :: saluta();
		std::cout << "\nSono uno studente con matricola " << matricola << " ed i miei voti sono:";
		for (int i = 0; i != 20; i++) {
			std::cout << "\n" << voti[i];
		}
		std::cout << "\nLa mia media è " << calcolaMedia();
	}

	~Studente(){
		matricola = "";
		delete[] voti;
	}
};

class Docente : public Persona {
public:
	int numInsegnamenti;
	int numStudenti;

	Docente(int i, int s, char n, char c) : Persona(n, c), numInsegnamenti(i), numStudenti(s) {}

	const void saluta() override {
		Persona::saluta();
		std::cout << "\nSono un insegnante che insegna " << numInsegnamenti << " materie per " << numStudenti << " studenti";
	}

	~Docente() {
		numInsegnamenti = 0;
		numStudenti = 0;
	}
};
int main() {
	Casa* casa1 = new Casa(22, 50);
	Casa* casa2 = new Casa(23, 100);
	Casa* casa3 = new Casa(24, 150);
	Casa* casa4 = new Casa(25, 200);
	Persona* p1 = new Studente("0253814", 'F', 'C');
	Persona* p2 = new Persona('F', 'T');
	Persona* p3 = new Persona('A', 'B');
	Persona* p4 = new Persona('C', 'D');
	Persona* p5 = new Persona('E', 'F');
	Persona* p6 = new Persona('G', 'H');
	Persona* p7 = new Persona('I', 'L');
	
	p1->trasloca(*casa1);
	p2->trasloca(*casa2);
	p3->trasloca(*casa3);
	p4->trasloca(*casa4);
	p5->trasloca(*casa1);
	p6->trasloca(*casa2);
	p7->trasloca(*casa3);

	p1->saluta();

	delete casa1;
	delete casa2;
	delete casa3;
	delete casa4;
}