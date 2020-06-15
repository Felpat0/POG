#include <cstring>
#include <cstdio>
#include <iostream>
#include <exception>
#include <vector>
#include <limits>

using namespace std; 


class MyException : public exception
{
	public:
	virtual const char* what() const noexcept // <- indica che questa funzione non lancera' nessuna eccezione
	{		
		return "La mia eccezione personale!";
	}
};


void throwingFunction()
{
	throw MyException();
}

int main(void)
{
	
	try 
	{
		cout << "Immetti un valore da lanciare come eccezione: ";
		int i; char c;
		if ( cin >> i )
		{	throw i;	}	
		else
		{
			cin.clear();
			if (cin >> c)
			{	throw c;	}
			else
			{	throw;		}
		}
	}
	catch (int e)
	{
		cout << "Eccezione intera di valore : " << e << endl;
	}
	catch (char e)
	{
		cout << "Eccezione char di valore : " << e << endl;
	}
	catch (...)
	{
		cout << "Eccezione generica!" << endl;
	}
	
	try
	{
		throw exception(); // <- la classe base delle eccezioni dell'std 
	}
	catch( exception e )
	{
		cout << "Eccezione di tipo " << e.what() << endl;
	}
	
	try
	{
		vector<int> vec (10,1);
		vec[0] = 1000;
		vec.at(15) = 15; // <- lancia un'eccezione di tipo out_of_range (deriva da logic_error : exception )
	}
	catch( exception& e ) // <- in questo modo catcha anche le eccezioni derivate da exception
	{
		cout << "Eccezione di tipo " << e.what() << endl;
	}
	
	int* p = nullptr;
	int size = -1;
	try
	{
		p = new int[size]; // <- bad_array_new_length (deriva da bad_alloc : exception )
		
	}
	catch ( bad_array_new_length& e )
	{
		p = new int[10]; // <- aggiro il problema
		cout << "Tentavo di istanziare un array con una lunghezza non accettata, lo istanzio invece con lunghezza 10!";
	}
	catch ( exception& e )
	{
		cout << "Eccezione di tipo " << e.what() << endl;
	}
	
	delete [] p;
	
	try
	{
		throw MyException();
	}
	catch ( exception& e )
	{
		cout << "Eccezione di tipo " << e.what() << endl;
	}
	
	try
	{
		throwingFunction();
	}
	catch ( exception& e )
	{
		cout << "Eccezione di tipo " << e.what() << endl;
	}
	
	try
	{
		try
		{
			throwingFunction();
		}
		catch ( MyException& e)
		{
			cout << "La intercetto come specificatamente e la rilancio" << endl;
			throw 10; 
			// throw e;
		}
	}
	catch ( exception& e )
	{
		cout << "La intercetto come generica : " << e.what() << endl;
	}
	catch ( int e )
	{
		cout << "La intercetto come int : " << e << endl;
	}
	
	return 0;
}