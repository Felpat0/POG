#include <iostream>


using namespace std;
 
// Functors o Function Objects sono oggetti che si richiamano come fossero funzioni
// sfruttando l'overload dell'operatore ()
class LessThan 
{
	const int val;
	public:
	LessThan(const int &v):val(v){}
	
	bool operator()(const int &x) const 
	{
		return x < val;
	}

};

// Si inizializzano come sempre
// 		NomeClasse nomeOggetto = NomeClasse(v);
// Solo che poi di solito gli oggetti vengono usati in questo modo:
// 		nomeOggetto.nomeFunzione();
// Mentre i functors cosi':
// 		nomeOggetto(x); <--- l'operatore () dell'oggetto

void whichIsLessThanX( int* arr, int size, LessThan ltX )
{
	for (int i = 0; i < size; i++ )
	{
		if ( ltX( arr[i] ) )
			cout << arr[i] << " " ;
	}
}

int main()
{
	LessThan lt42 = LessThan(42);
	
	cout << "5 e' minore di 42 ? " << lt42(5) << endl;
	
	int array [5]= { 5, 10, 15, 30, 45 };
	
	cout << "\nQuali sono minori di 42?" << endl;
	whichIsLessThanX( array, 5, lt42 );
	cout << "\nQuali sono minori di 30?" << endl;
	whichIsLessThanX( array, 5, LessThan(30) );
	cout << "\nQuali sono minori di 12?" << endl;
	whichIsLessThanX( array, 5, LessThan(12) );
	
	return 0;
	
	
}