#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits> // <- per usare numeric_limits<>
#include <sstream>

// NOTA: spostarsi esplicitamente su questa cartella prima di eseguire il programma!

using namespace std;

vector<int> read_ints(istream& input)
{
	vector<int> res;
	int i;
	while (input >> i)
	{
		res.push_back(i);
	}
	return res;
}

int main(void)
{
	// Prendiamo un input dallo stream di input standard cin
	int n;
	cin >> n;
	cout << "n : " << n << endl;
	
	double db; // "2.5"
	cin >> n >> db; // "2" dentro n, ".5" dentro db
	cout << "n : " << n << " d : " << db << endl; // "n : 2 d : 0.5"
	
	string name;
	cin >> name;
	cout << "nome: " << name << endl;
	 
	cin.clear(); // Ripulisce lo stato dello stream 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora il resto delle cose inserite 

	cout << "Inserisci quanti numeri vuoi, se inserisci una parola il seguente ciclo si ferma" << endl;
	while ( cin >> n )
	{
		cout << "Hai inserito il numero " << n << endl;
	}
	cout << "Adesso stream ha un flag di errore, se non lo si ripristina le future operazioni di lettura potrebbero non funzionare!" << endl;
	cin.clear(); // Ripulisce lo stato dello stream 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora il resto delle cose inserite 

	
	getline(cin, name); // http://www.cplusplus.com/reference/string/string/getline/
	cout << "Nome per intero : " << name << endl;

	
	cout << "Inserisci una serie di interi " << endl;
	vector<int> intVec = read_ints(cin);
	for (auto i : intVec)
		cout << i << " ";
	cout << endl;
	
	// Formatting
	// Possiamo manipolare la formattazione dell'output tramite manipulators
	// che si trovano in <ios> <istream> <ostream> <iomanip>
	int a = 1234;
	cout << a << " " << hex << a << " " << oct << a << "\n" ;
	
	double d = 123.456;
	cout << d << "\n" 
			<< scientific << d << "\n"		
			// << hexfloat << d << "\n" // Non supportato da questa versione del compiler
			<< fixed << d << " \n"
			// << defaultfloat << d << "\n" // Non supportato da questa versione del compiler
			<< "\n";
	
	cout.precision(8);
	cout << 1234.56789 << " " << 123456789 << " " <<  dec << 123456789 << endl;
	cout.precision(4);
	cout << 1234.56789 << " " << 123456789 << endl;
	
	// Lettura / Scrittura su Files
	
	/*
	app		(append) Set the stream's position indicator to the end of the stream before each output operation.
	ate		(at end) Set the stream's position indicator to the end of the stream on opening.
	binary	(binary) Consider stream as binary rather than text.
	in		(input) Allow input operations on the stream.
	out		(output) Allow output operations on the stream.
	trunc	(truncate) Any current content is discarded, assuming a length of zero on opening.
	*/
	ofstream ofs("nomefile_da_scrivere.txt", ios::app);
	ofs << "Scriviamo qualcosa \n dentro \n questo file.";
	ofs << "\n E pure questo!";
	ofs.close();
	
	ifstream ifs("nomefile_da_leggere.txt", ios::in);
	if ( !ifs) cout << "File non aperto!" << endl; 
	// Attenzione, se non si esegue il programma dalla cartella corretta (quella che contiene l'exe) il file non viene trovato
	// (e nel caso di ofs viene scritto nella cartella errata) , per questo e' importante spostarsi su questa cartella prima di eseguire questo programma
	string s;
	getline( ifs, s );
	ifs.close();
	cout << s << endl;
	
		
	ifstream ifs2("numeri.txt");
	int tabCounter = 0;
	while (ifs2)
	{
		
		for(int i; ifs2>>i; )
		{
			for(int t = 0; t < tabCounter; t++) 
				cout << "\t";
			cout << i << endl;
		}
		
		if (ifs2.eof() ) // Controlliamo se lo stream e' arrivato alla fine del file
		{
			cout << "End of file" << endl;
		}
		else if( ifs2.fail() )
		{
			ifs2.clear(); // Potrebbe essere un errore recuperabile
			char ch;
			if ( ifs2 >> ch )
			{
				switch(ch)
				{
					case '{': tabCounter++; break;
					case '}': tabCounter--; break;
					default: ifs2.setstate(ios_base::failbit); // Assegno lo stato di errore allo stream
				}
			}
		}
	}
	ifs2.close();
	
	// String Streams
	ostringstream oss;
	double dtf = 123.456789;
	oss << "{temperature," << scientific << dtf << "}";
	cout << oss.str() << endl; // str() <- leggo lo stream in una stringa
	
	string numeri = "12 34 56 78 90 NaN 0 12";
	istringstream iss(numeri);
	cout << dec;
	
	while(iss)
	{
		int i;
		if (iss>>i)
		{
			cout << i << " e' un numero!" << endl;
		}
		else if (iss.eof() )
		{
			cout << "E' finito lo stream!" << endl;
		}
		else
		{
			iss.clear();
			string p;
			if (iss >> p)
			{
				cout << p << " e' una parola!" << endl;
			}
			else
			{
				iss.setstate(ios_base::failbit);
			}
		}
	}
	
	return 0; 
}