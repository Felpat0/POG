#include <iostream>


using namespace std;


int main()
{
	string s = "Una stringa! Finalmente verranno allocate/deallocate autonomamente!";
	cout << s << endl;
	// Ergo non servira fare delete s;
	
	string* ps = new string("Purtuttavia questo e' un puntatore ad una stringa, percio' andra' deallocato manualmente");
	cout << *ps << endl;
	// Ed andra' fatto, come al solito
	delete ps;
	
	string s1 = "Le stringhe sono simili a quelle di Java, ";
	string s2 = "possiamo concatenarle con gli operatori +";
	s1 = s1 + s2;
	s1 += " e += \n";
	cout << s1;
	
	// Ed hanno anche delle funzioni per manipolarle come ad esempio
	string stringa = "Voglio estrarre da QUI a QUI precisamente";
	cout << "-" << stringa.substr( 19, 9 ) << "-" << endl ;
	
	stringa = "Adesso invece voglio sostituire i primi 6 caratteri con una stringa piu' lunga";
	cout << stringa.replace(0, 6, "Questa volta" ) << endl;
	
	stringa = "O magari trovare la prima occorrenza di una 'sottostringa' specifica";
	int primaO = stringa.find("O");
	int primoCharDiPrima = stringa.find("prima");
	cout << "La prima 'O' si trova in " << primaO << " mentre il primo char di 'prima' si trova in " << primoCharDiPrima << endl;
	cout << "Infatti " << stringa[ primaO ] << " e " << stringa.at( primoCharDiPrima ) << endl;
	
	stringa = "Si puo' anche ricavare il corrispettivo in C-style";
	const char* cstylestring = stringa.c_str();
	cout << cstylestring << endl;
	
	// Ci sono anche altre funzioni, ma potete facilmente trovarle da voi...
	
	// Infine, esiste un tipo di stringa chiamato raw literal string che inizia con: R"( e finisce con )" 
	// la differenza con una stringa normale e' che non processa i caratteri escape come \t e \n 
	stringa = "\nPrima riga.\nSeconda riga.\nTerza riga.\n";
	cout << stringa << endl;
	stringa = R"(\nPrima riga.\nSeconda rica.\nTerza riga.\n)";
	cout << stringa << endl;
	
	return 0;
}