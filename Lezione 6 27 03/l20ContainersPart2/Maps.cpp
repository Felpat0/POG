#include <iostream>
#include <map>
#include <unordered_map>


using namespace std;

// ELEMENTI PER MAP
struct Casella
{
	char riga; int colonna;
	Casella(char riga,int colonna):riga(riga),colonna(colonna){};
	
	bool operator<(const Casella& p) const
	{ 
		if ( riga < p.riga ) return true;
		else if ( riga == p.riga && colonna < p.colonna ) return true;
		else return false;
	}
	
	friend std::ostream& operator<<( std::ostream &output, const Casella &c );
};
ostream& operator<<( ostream &output, const Casella &c ) // Non devo ripetere il friend
{
	return output << c.riga << c.colonna;
}

// ELEMENTI PER UNORDERED MAP
struct KeyPersonaggio
{
	string nome, classe;
	int livello;
	KeyPersonaggio(string n,string c,int l):nome(n),classe(c),livello(l){}
	// Una chiave custom per le mappe non ordinate DEVE fare l'overload dell'operatore ==
	// per fargli gestire i casi di hash collision 
	bool operator==(const KeyPersonaggio &kpg) const
	{
		return ( nome == kpg.nome && classe == kpg.classe && livello == kpg.livello );
	}
};
// Inoltre DEVE fornire un metodo per calcolare il codice hash, e si puo' fare in due modi
// Modo 1) specializzando l'hash del namespace std
namespace std
{
	template <>
	struct hash<KeyPersonaggio>
	{
		std::size_t operator()(const KeyPersonaggio& kpg) const
		{
			
			// Creo le struct per effettuare l'hash di stringhe e interi
			// eseguo un hash alla volta, effettuando degli shift su due di essi
			// per ridurre le possibili collisioni di codice hash o
			// l'annullamento dell'operatore bitwise XOR (^)
			return ((hash<string>()(kpg.nome)) 
			^ (hash<string>()(kpg.classe) << 1 )
			^ hash<int>()(kpg.livello) >> 1 );

			// hash<KeyPersonaggio>()(PERSONAGGIO);
		}
	};


}
// Modo 2) definire un functor che esegua l'hash (senza metter mano all' std)
struct KeyPersonaggioHasher
{
	std::size_t operator()(const KeyPersonaggio& kpg) const
	{
		return ((hash<string>()(kpg.nome)) 
			^ (hash<string>()(kpg.classe) << 1 )
			^ hash<int>()(kpg.livello) >> 1 );
	}	
};


int main()
{
	// Le mappe sono dei contenitori associativi che associano una chiave (key) ad un valore (value)
	// e sono solitamente implementati come alberi binari (la cui ricerca di elementi sfrutta la binary search ed offre una velocita' di O(log(n))  )
	// cio' richiede che le chiavi siano comparabili tramite operatore <, poiche' l'algoritmo di iterazione/ricerca/inserimento deve valutare
	// gli elementi a due a due per decidere dove/come manipolarli
	
	// nel seguente caso le chiavi sono string mentre i valori sono int
	std::map< string, int> mapSkIv { {"Primo",1}, {"Beta",2}, {"La Risposta",42} };
	cout << "Quante strade un uomo fara'?" << mapSkIv["La Risposta"] << endl; // Per accedere ad un elemento si utilizza l'operatore [] passando la chiave come argomento
	
	// La stessa operazione, nel caso in cui non trovi un elemento lo aggiungera' con valore di default (senza avvertimento alcuno) 
	cout << "Quanti erano i moschettieri del re? " << mapSkIv["moschettieri"] << endl;
	// E' possibile anche effettuare un'assegnazione sempre con lo stesso operatore 
	mapSkIv["moschettieri"] = 3; 
	cout << "Come scusa? " << mapSkIv["moschettieri"] << " ... ah ecco!\n\n" << endl;
	
	// Gli oggetti utilizzati come chiavi DEVONO effettuare l'overload dell'operatore <
	// perche' le mappe sono ordinate e tale operatore viene utilizzato per effettuare l'ordinamento
	map< Casella, string > scacchiera { { {'A',3},"Re"}, { {'B',2},"Regina"} };
	scacchiera[ Casella('A',6) ] = "Alfiere";
	cout << "Chi c'e' in A3 ? " << scacchiera[ Casella('A',3 ) ] << endl;
	
	// Anche le mappe hanno le loro funzioni da container
	// Per inserire un elemento tramite insert, abbiamo tre possibilita':
	// 1) utilizzare std::map<type1,type2>::value_type( type1Obj, type2Obj ) che e' il tipo specifico della mappa in questione
	// map<typeK,typeV>::value_type( key,value )
	scacchiera.insert( std::map<Casella, string>::value_type( Casella('F',4) , "Basito") );
	// 2) passare un oggetto di tipo std::pair<type1,type2> (che fara' un cast per avere alla fine il value_type corretto)
	scacchiera.insert( std::pair< Casella, string> ( Casella('C',4), "Torre" ) );
	// 3) passare std::make_pair( obj1, obj2) che capisce il tipo dei dati tramite deduzione di template e potrebbe generare oggetti di tipo diverso rispetto al desiderato
	// e potrebbe quindi richiamare pair<type1,type2> per effettuare il cast 
	scacchiera.insert(std::make_pair( Casella('E',3), "Cavallo"));
	
	// Per velocizzare l'inserimento possiamo dare un hint (indizio) sulla posizione in cui andra' inserito, utilizzando gli iteratori
	// L'ottimizzazione massima avviene se l'iteratore puntera' all'elemento successivo rispetto a dove andra' inserito l'elemento 
	map<Casella,string>::iterator scacchIterator = scacchiera.end(); // Punta al "subito dopo l'ultimo elemento"
	advance( scacchIterator, - 1 ); // Punta all'ultimo elemento 
	cout << "\nL'ultimo elemento e' " <<  scacchIterator->second << endl; // il significato di "->second" e' descritto poco piu' in basso
	scacchiera.insert( scacchIterator, pair<Casella,string> ( Casella('E',4), "Pedone") );
	
	cout << "\nE in C3 ? " << scacchiera[ Casella('C',3) ] << endl;
	cout << "\nF4 ? '" << scacchiera[ Casella('F',4) ] << "'" << endl;
	
	// Anche in questo caso possiamo usare emplace per non effettuare copie
	scacchiera.emplace( Casella('B',1), "Basement" );
	
	
	// Posso scorrere una mappa con gli iteratori
	for ( map<Casella,string>::iterator mapIter = scacchiera.begin(); mapIter != scacchiera.end(); ++mapIter )
	{
		// Gli iteratori pero' puntano a delle pair (coppie), quindi per accedere agli elementi bisogna accedere ai loro campi
		// pair.first restituisce il primo elemento (la chiave), pair.second restituisce il secondo (il valore)
		// ma gli iteratori funzionano come i puntatori, quindi bisogna dereferenziare
		cout << mapIter->second << " in " << mapIter->first << endl;
	}
	
	cout << "\n\n";

	// Un altro modo per ciclare sulla mappa
	for (auto &p : scacchiera)
	{
		cout << p.second << " in " << p.first << endl;
	}
	
	// Accedere con l'operatore [] porta sempre il rischio di aggiungere un elemento con valore di default, invece che riceverne uno 
	// per ovviare a questo problema si utilizza il metodo at(), che pero' lancera' un'eccezione nel caso in cui non venga trovata la key
	cout << "\nIn A6 c'e' " << scacchiera.at( Casella('A',6) );
	
	// Se non si e' sicuri se un oggetto e' presente, si puo' usare il metodo find( key ); che restituisce un iteratore a quell'elemento se e' presente
	// o un iteratore a container.end() se non e' presente (ho specificato container perche' non vale solo per le mappe)
	cout << "\nC'e' qualcuno in F3 ? " ;
	map<Casella,string>::iterator mapIter = scacchiera.find( Casella('F',3) );
	if ( mapIter  != scacchiera.end() ) // vi ricordo che end() restituisce l'elemento "dopo l'ultimo" quindi non c'e' rischio di confondersi con l'ultimo!
	{
		cout << "Si!" <<  mapIter->second << endl;
	}
	else
	{
		cout << "No!" << endl;
	}
	
	mapIter = scacchiera.find( Casella('F',4) );
	if ( mapIter  != scacchiera.end() )
	{
		cout << "Ed in F4 c'e' " <<  scacchiera[ Casella('F',4) ] << endl;
	}
	
	// Ovviamente possiamo utilizzare anche in questo caso erase() per rimuovere elementi
	// Mostriamo solo il caso dell'erase tramite range.
	// La validita' degli iteratori e' preservata per tutti gli iteratori CHE NON PUNTANO AGLI ELEMENTI RIMOSSI
	mapIter = scacchiera.find( Casella('C',4 ) );
	auto mapIterEndRange = mapIter;
	++mapIterEndRange; ++mapIterEndRange;
	scacchiera.erase( mapIter, mapIterEndRange );
	cout << endl;
	for (auto &p : scacchiera)
	{
		cout << p.second << " in " << p.first << endl;
	}
	
	// Le unordered_maps sono simili alle mappe, ma invece che ordinare gli elementi tramite albero binario associano gli elementi
	// a dei buckets in base al valore hash delle chiavi, in modo da garantire un accesso rapido agli elementi
	// tale accesso offre una velocita' di O(1) se gli hash code delle chiavi sono tutti unici (e quindi ogni bucket contiene
	// una sola coppia key,value ) ma rallenta quando si cercano chiavi che hanno collisioni di hash tra di loro (quindi il bucket
	// di quell'hash contiene piu' di una coppia key,value ), il caso peggiore e' quando tutte le chiavi presentano lo stesso 
	// valore hash e quindi c'e' un unico bucket, in tal caso l'accesso ha velocita O(n)
	// Sono migliori delle maps per l'accesso diretto ad un determinato elemento, ma meno efficienti per l'iterazione in range 
	
	// I metodi begin() ed end() delle unordered maps restituiscono gli iteratori del container come gli altri containers,
	// ma se gli si passa un intero i, essi restituiranno gli iteratori del bucket i-esimo
	// Vediamo come mostrare il numero di buckets e quali elementi si trovano in ciascuno con un esempio
	std::unordered_map< string, string> mymap = {
            {"house","maison"},
            {"apple","pomme"},
            {"tree","arbre"},
            {"book","livre"},
            {"door","porte"},
            {"grapefruit","pamplemousse"}
	};

	unsigned n = mymap.bucket_count();

	cout << "mymap has " << n << " buckets.\n";

	for (unsigned i=0; i<n; ++i) {
		cout << "bucket #" << i << " contains: ";
		for (auto it = mymap.begin(i); it!=mymap.end(i); ++it)
			cout << "[" << it->first << ":" << it->second << "] ";
		cout << "\n";
	}
	cout << "\n\n\n";
	
	// Per implementare come chiavi delle classi custom tali classi hanno due requisiti:
	// 1) implementare l'override dell'operatore ==
	// 2) deve esistere una classe che crei il codice hash (solitamente si usa un functor)
	// Vedere in cima al file per l'esempio seguente:
	
	// In questo modo viene utilizzata la specializzazione dell'std 
	unordered_map< KeyPersonaggio, string > battlecries;
	battlecries[ KeyPersonaggio("Alejandro","Dancer",1) ] = "Don't call my name!";
	battlecries[ KeyPersonaggio("Gandalf","Grey Wizard",50) ] = "You shall not pass!";
	battlecries[ KeyPersonaggio("Will Ferrell","Anchorman",12) ] = "Well, that escalated quickly.";
	for (auto it = battlecries.begin(); it != battlecries.end(); ++it )
	{
		cout << it->first.nome << ": " << it->second << endl;
	}
	
	// In questo modo invece specifico il functor che calcolera' l'hashcode (il terzo type dichiarato tra parentesi angolari)
	unordered_map< KeyPersonaggio, string, KeyPersonaggioHasher > deathrattles;
	deathrattles[ KeyPersonaggio("Richard III","King",7) ] = "My kingdom for a horse!";
	deathrattles[ KeyPersonaggio("Gandalf","Grey Wizard",50) ] = "Fly you fool...";
	deathrattles[ KeyPersonaggio("T-800","Terminator",99) ] = "I'll be back.";
	for (auto it = deathrattles.begin(); it != deathrattles.end(); ++it )
	{
		cout << it->first.nome << ": " << it->second << endl;
	}
	
	// Anche in questo caso possiamo utilizzare i metodi insert, emplace, erase...
	// Effettuando un erase restano validi tutti gli iteratori che NON PUNTANO AGLI ELEMENTI RIMOSSI
	// Aggiungendo elementi invece gli iteratori restano validi a meno che la manipolazione della mappa non causi un rehashing
	// ovvero il processo che ricrea la mappatura dei codici hash utilizzati per accedere agli elementi
	// modificando quindi i buckets. Cio' avviene se il load_factor della mappa supera il suo max_load_factor
	// il load_factor e' calcolato tramite mappa.size()  (il numero totale di elementi)  diviso mappa.bucket_count() (il numero di buckets)
	// solitamente max_load_factor e' inizialmente uguale ad 1 
	cout << "Size : " << deathrattles.size() << endl;
	cout << "Buckets count : " << deathrattles.bucket_count() << endl;
	cout << "Load factor : " << deathrattles.load_factor() << endl;
	cout << "Max load factor : " << deathrattles.max_load_factor() << endl;
	
	return 0;
	
	
}