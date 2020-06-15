// function template
#include <iostream>
using namespace std;


// Metodi con template
template <typename T>
T GetMax (T a, T b) {
  T result;
  result = (a>b)? a : b;
  return (result);
}

template <class T, class U>
T GetMin (T a, U b) {
  T result;
  result = (a<b)? a : b;
  return (result);
}


void templateMethodsTest () {
  int i=5, j=6, k;
  long l=10, m=5, n;
  k=GetMax<int>(i,j);
  n=GetMax<long>(l,m);
  cout << k << endl;
  cout << n << endl;
  
  k = GetMin<int,long>(i,l);
  n = GetMin<long,int>(m,j);
  cout << k << endl;
  cout << n << endl;

}

// Classe con template
template <class T>
class mypair {
    T a, b;
  public:
    mypair (T first, T second);
	  T getMax ();
};

template <class T>
mypair<T>::mypair(T f, T s)
{
	a = f; b = s;
}

template <class T>
T mypair<T>::getMax()
{
	return ( a > b ) ? a : b;
}

void templateClassTest()
{
	mypair<int> myIntPair( 25,50);
	cout << myIntPair.getMax() << endl;
}

// Le template class non sono vere e proprie classi ma ricette, di per se' non vengono compilate
// vengono create/compilate solo quando il compilatore trova un'instanza di un determinato tipo specifico
// (ad esempio mypair<int> )
// La conseguenza di cio' e' che non possiamo utilizzare la solita struttura myclass.cpp myclass.h 
// ed includere nel mymain.cpp solo il myclass.h, questo perche' quando compileremo myclass.cpp 
// esso non trovera' alcuna instanza specifica myclass<unqualchetipo> e quindi il linker dara' errore successivamente.
// Per risolvere la situazione ci sono diverse strategie due delle quali sono:
// 1)	Includere l'implementazione direttamente nell'header (includere il codice di myclass.cpp dentro myclass.h )
// 		in questo modo la classe verra' compilata poiche' in mymain.cpp vengono instanziate le varie myclass<qualchetipo>
// 2)	Inserire alla fine del file myclass.cpp tutte le possibili combinazioni di instanza del template tramite la formula
//		template class myclass<TIPOSPECIFICO>;
//		in questo modo pero' il resto del programma potra' utilizzare il template solo con i tipi specifica qui definiti
//
//	Solitamente viene preferito il metodo 1)


// Template specialization
// class template:
template <class T>
class mycontainer {
    T element;
  public:
    mycontainer (T arg) {element=arg;}
    T increase () {return ++element;}
	  T get() { return element; }
};

// class template specialization:
template <>
class mycontainer <char> {
    char element;
  public:
    mycontainer (char arg) {element=arg;} // Dobbiamo riscrivere tutto, non c'è inheritance
    char increase() { return uppercase(); }    
    char uppercase ()
    {
      if ((element>='a')&&(element<='z'))
      element+='A'-'a';
      return element;
    }
};

void templateSpecializationTest () {
  mycontainer<int> myint (7);
  mycontainer<char> mychar ('j');
  cout << myint.increase() << endl;
  cout << mychar.uppercase() << endl;
}

// Non-type parameters 
// sequence template
template <class T, int N>
class mysequence {
    T memblock [N];
  public:
    void setmember (int x, T value);
    T getmember (int x);
};

template <class T, int N>
void mysequence<T,N>::setmember (int x, T value) {
  memblock[x]=value;
}

template <class T, int N>
T mysequence<T,N>::getmember (int x) {
  return memblock[x];
}

void templateNonTypeParametersTest () {
  mysequence <int,5> myints;
  mysequence <double,5> myfloats;
  myints.setmember (0,100);
  myfloats.setmember (3,3.1416);
  cout << myints.getmember(0) << '\n';
  cout << myfloats.getmember(3) << '\n';
}

// Default values or type 
template <class T=char, int N = 10>
class defaultSequence
{
	T memblock [N];
	public:
    void setmember (int x, T value);
    T getmember (int x); 
};

template <class T, int N>
void defaultSequence<T,N>::setmember (int x, T value) {
  memblock[x]=value;
}

template <class T, int N>
T defaultSequence<T,N>::getmember (int x) {
  return memblock[x];
}

void templateDefaultParametersTest () {
  defaultSequence <> defaultSeq;
  defaultSequence <int> intSeq;
  defaultSeq.setmember (0,'a');
  intSeq.setmember (3,9);
  cout << defaultSeq.getmember(0) << '\n';
  cout << intSeq.getmember(3) << '\n';
}

// MAIN 
int main()
{
	templateMethodsTest();
	templateClassTest();
	templateSpecializationTest();
	templateNonTypeParametersTest();
	templateDefaultParametersTest();
	return 0;
}