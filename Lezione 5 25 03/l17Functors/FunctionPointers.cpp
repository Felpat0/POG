#include <iostream>


using namespace std;

int myFunc()
{
	return 5;
}

int myOtherFunc()
{
	return 8;
}

/*
void f1()
{
	cout << "Da dentro la funzione " << myFunc() << endl;
}

void f2()
{
	cout << "Da dentro la funzione " << myOtherFunc() << endl;
}
*/

void funcWithFunctionPtrParameters( int(*afptr)() )
{
	cout << "Da dentro la funzione " << afptr() << endl;
}  

void funzioneCheRestituisceVoidEPrendeInInputUnInt ( int n )
{
	cout << "L'intero passato in input a questa funzione e' " << n << endl;
}

int main()
{
	cout << "MyFunc() = " << myFunc() << endl;
	cout << "MyFunc = " << myFunc << endl; // Senza le parentesi tonde restituisce l'indirizzo della funzione
	
	// Creo un puntatore ad una funzione
	// La prima cosa che scrivo e' il tipo di dato restituito (void)
	// Poi metto tra parentesi l'asterisco seguito dal nome del puntatore:    (*nomePUntatore)
	// Poi metto tra paretnesi tonde i parametri che prenderanno in input le funzioni cui puo' puntare questo puntatore (int n)
	void (*nomePuntatore)(int param);
	// Lo assegno passandogli il nome della funzione senza le parentesi tonde
	nomePuntatore = funzioneCheRestituisceVoidEPrendeInInputUnInt;

	// Richiamiamo quindi la funzione tramite il puntatore!
	nomePuntatore( 8 );

	int (*fncPtr)() = myFunc; // <-- un puntatore di una funzione che non prende parametri e restituisce int
	
	cout << "*fncPtr() = " << (*fncPtr)() << " or " << fncPtr() << endl;
	
	fncPtr = myOtherFunc;
	
	cout << "*fncPtr() = " << fncPtr() << endl;
	
	funcWithFunctionPtrParameters( myFunc );
	funcWithFunctionPtrParameters( fncPtr );
	
	return 0;
	
	
}