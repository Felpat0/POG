#include "MyPair.h"
#include <iostream>

using namespace std;

template <typename T, typename U>
void pair_print_test(MyPair <T> &p1, MyPair <U> &p2)
{
    p1.print();
	p2.print();
	cout << endl;
}


int main(int argc, char** argv) {
    
    MyPair<int> intPair( 3, 5);
	MyPair<double> doublePair( 12.2345, 67.89 );

	MyPair<int> altraIntPair = intPair *=3;
	 
	
	MyPair<double> sommaDouble = doublePair + intPair;
	MyPair<int> sommaInt = intPair + doublePair;
	cout << endl;
	pair_print_test( intPair, doublePair );
	pair_print_test( sommaInt, sommaDouble );
		
	pair_print_test<double,int>( doublePair, intPair );
    
	//MyPair<int> altroInt = intPair.sum( sommaInt );  // <- Non puo' dedurre da sola il tipo di ritorno (ha un altro typename)
	//MyPair<int> altroInt = intPair.sum<int,int>( sommaInt );
	// quindi devo specificarlo
	MyPair<int> altroInt = intPair.sum<int>( sommaInt );
	altroInt.print();
	
	MyPair<double> altroDouble = intPair.template sum<double>( sommaInt ); // <- Un altro modo per specificare quando si richiama un metodo template
	altroDouble.print();
	
    return 0;
    
}