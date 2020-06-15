#include <iostream>

using namespace std;

class MyInt
{
	public:
	int i;

	MyInt(int _i) : i(_i) {}

	MyInt operator+(MyInt other)
	{
		MyInt result(0);
		result.i = i + other.i;
		// MyInt result( i + other.i );
		return result;
		// return MyInt( i + other.i );
	}

	MyInt operator+(int n)
	{
		MyInt result(0);
		result.i = i + n;
		return result;
	}

	MyInt operator-(MyInt other)
	{
		MyInt result(0);
		result.i = i - other.i;
		return result;
	}

	MyInt operator-(int n)
	{
		MyInt result(0);
		result.i = i - n;
		return result;
	}


	void operator+=(const MyInt& a) // Operatore di assegnazione, l'argomento e' l'elemento a destra
	{
		i += a.i;		
	}

	void operator+=(const int& n) // Operatore di assegnazione, l'argomento e' l'elemento a destra
	{
		i += n;		
	}

	MyInt operator++() // Operatore di incremento, senza parametro si effettua l'overloading di ++var; (prefix)
	{
		i += 1;
		return *this; // *this restituisce il valore di MyInt, ovvero una copia in cui i campi hanno il medesimo valore dell'originale
	}
	
	MyInt operator++(int) // Operatore di incremento, col parametro 'int' si effettua l'overloading di var++; (postfix)
	{
		MyInt a = *this;
			
		++*this;
		// ovvero
		// i += 1;
			
		return a;
	}

	
};

// Per implementare l'operatore tenendo un int a sinistra e un MyInt a destra dobbiamo usare una free function
// ovvero una funzione fuori da qualsivogia classe
MyInt operator+(int n, MyInt m)
{
	MyInt result( n + m.i );
	return result;
}


// overload dell'operatore di inserimento
// NON e' nello scope della classe, quindi la struttura e' :  returnType operator ( elementoASinistra, elementoADestra) (come nel caso degli Enum)
// nel caso specifico fa l'overload di:    cout << oggettoArma; 
// cout : elemento di sinistra (di tipo ostream )
// oggettoArma : elemento di destra (di tipo const Arma& )
ostream& operator<<( ostream& output, const MyInt &a ) // Non devo ripetere il friend
{
	output << " MyInt( i: " << a.i << " ) ";
	return output;
}

int main()
{
	MyInt num1 = MyInt(10);
	MyInt num2 = MyInt(40);
	MyInt numRes = num1 + num2;
	//MyInt numRes = num1 + MyInt(40);
	cout << "Il nuovo MyInt ha come valore " << numRes.i << endl;
	numRes = numRes + 100;
	cout << "Il nuovo MyInt ha come valore " << numRes.i << endl;
	
	
	num1 += numRes;
	cout << " num1 += numRes ----> " << num1 << endl; // <- scrivo solo num1 perche' uso l'overload dell'operatore <<
	num1 += 10;
	cout << " num1 += 10     ----> " << num1 << endl;

	MyInt num {1}; 
	cout << " ++num ---> " << ++num << endl;
	cout << " num++ ---> " << num++ << endl;
	cout << " num   ---> " << num << endl;

	// Se l'operatore << non restituisse un ostream, non potrei concatenare le operazioni
	cout << " num --> ";
	cout << num;
	cout << endl;
	// Alla stessa maniera posso concatenare delle addizioni perche' ogni operatore  n + m   mi restituisce un nuovo int
	int a = 1 + 2 + 3 + 4 + 5 + 6;


	MyInt res = 1000 + MyInt(555);
	cout << "Tramite l'operatore come free function " << res.i << endl;

	
}