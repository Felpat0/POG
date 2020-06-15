#include <iostream>
//#include <cstddef>

using namespace std;


// Funzioni dimostrative REFERENCE
void modifyIntByPointer( int *a ) 
{
    cout << " modifyIntByPointer " << endl;
    // Copia il valore del puntatore (l'indirizzo di memoria) di conseguenza posso modificare il valore a cui punta.
    *a += 10;  
    // Ma potrei cambiare anche il valore del puntatore copiato,
    int altroInt = 99;
    a = &altroInt;
    *a = 10000;
    // Adesso ho modificato il valore di 'altroInt' ma non quello della variabile cui puntava
    // il puntatore passato come argomento 
    // Inoltre il puntatore originale non e' stato modificato, quello al di fuori di questa funzione
    // punta ancora alla variabile di partenza (all'indirizzo dove si e' eseguito *a += 10, per intenderci)  

} 

void modifyTheCopy ( int a )
{
    a += 10; // viene modiicata solo la copia
}

void modifyIntByReference ( int &a )
{
    a += 10;
    
    // 'a' fara' sempre riferimento allo stesso indirizzo dell'argomento passato
    // non posso in alcun modo modificare l'indirizzo cui fa riferimento 
    // inoltre questa pratica non prevede la copia di nessun valore 
}

void modifyPtrArray( int* a )
{
    a[2] = 15; // e' come scrivere *(a+2) 
    // Ovvero parto dal primo elemento dell'array e mi sposto di due, assegno 15 a quest'indirizzo raggiunto.

    // Gli array quando vengono passati decadono a puntatori

/*
        Leggete sotto per questo caso
    int b [] = { 0, 1, 2};
    a = &b;

    a[1] = 15; // <- sto modificando b e non l'array originale
    */
}

void modifyPtrArrayByReference( int* &a)
{
    a[3] = 25;

    //a = &nomeAltroArray; // <- sto modificando l'array che viene puntato dal puntatore nel main
    // (leggete sotto)
}

void modifyPtrByCopy (int * a) // la variabile a viene copiata
{
    *a += 15;
    int b = 10;
    a = &b; // viene modificata la copia
}

void modifyPtrByReference(int * &a) // la vriabile a "FA RIFERIMENTO" a qualsiasi puntatore di interi gli passo
{
    *a += 15;
    int b = 10;
    a = &b; // viene modificato il puntatore nel main
}



void cycleArrayByPreciseRange( int (&array)[10] ) // Passa un array tramite reference, l'array pero' dovra' essere esattamente di 10 elementi (in questo caso)
{
    for (int i = 0; i < 10; i++)
        cout << " " << array[i];
        
    cout << endl;
}
 
void dontModifyButDontCopyInt( const int &a )
{
    // Le funzioni senza reference fanno copie dei dati, quindi sono piu' onerose
    // ma salvaguardano le variabili originali passate (gli argomenti non vengono modificati)
    // Se volessimo questa 'sicurezza' senza l'onere di copiare i dati possiamo usare questo costrutto
    
    cout << "Non posso modificare il valore " << a << " ma cosi' non l'ho neanche copiato!" << endl;
}


// Funzioni CONST
int square (int x )
{
    return x * x;
}

int somma( const int a, const int b) // a e b non verranno modificati
{
    // a += 10; // Errore
    return a + b;
}
///////////////////////////////




void moltiplicaPer( int* a, int* b, int multiplier)
{
    *a *= multiplier + 1;
    *b *= multiplier + 2;
}

int ricorrenzeX ( char* s, char x )
{ 
    if ( s == nullptr ) return 0;
    int counter = 0; 
    for (; *s!= 0; s++) // Funziona solo se l'ultimo carattere dell'array e' '\0'
    {
        cout << *s;
        if ( *s == x )
            counter++;
    }
    
    return counter;
}

int main ()
{    

    
    // for 'each' (range)
    int myArr [] = {0,1,3};
    for (auto x : myArr )
    {
        cout << x << endl;
    }
  
    
    char cString [7] = {'H','i',' ','y','o','u', '\0'};
    cout << " ricorrenze di u in " << cString << " = " <<  ricorrenzeX(  cString , 'u' );
    
    
    
    // Stringhe c-Style
    char string1 [5] = "Yeah"; // Devo lasciare uno spazio in piu' per il carattere '\0'
    char string2 [] = "Yeah"; // Lo spazio necessario viene posto automaticamente
    char* string3 = (char*)"Yes"; // Senza il cast e' deprecato, vedremo piu' avanti le string 
    
    cout << endl << string1 << " " << string2 << " " << string3;
    
    
    // Prendere valori in input
    char cinput;
    
    cout << endl << "Inserisci un carattere : " ;
    //std::cin >> cinput;
    cin >> cinput;
    cout << "Hai inserito " << cinput << endl;
    switch ( cinput )
    {
        case 'Y':
            cout << "Ignoro le maiuscole : ";
        case 'y':
            cout << "y sta per Yes!" << endl;
            break;
        case 'N':
            cout << "Ignoro le maiuscole : ";
        case 'n':
            cout << "n sta per No!" << endl;
            break;
        
        default:
            cout << "Opzione di default" << endl;
            
    }
    
    // Const
    
    const int dmv = 17; // dmv is a named constant
    int var = 17; // var is not a constant
    const int max3 = 4 * square(var); // Ok, may be evaluated at run time
       
    int par1 = 3;
    int par2 = 5; 
    int const s1 = somma( par1, par2 ); // OK: evaluated at run time
        
    // Con i puntatori e casi complessi... 
    // Prendendo da Stack Overflow (sempre sia lodato)
    
    // "Read it backwards" (as driven by Clockwise/Spiral Rule)...
    int puntato = 1;
    
    int* pti ; // - pointer to int
    int const * ptci ; //- pointer to const int
    int * const cpti = &puntato; // - const pointer to int
    int const * const cptci  = &puntato; // - const pointer to const int

    /* Now the first const can be on either side of the type so:
    const int * == int const *
    const int * const == int const * const
    */
    
    int * puntatoreApuntato = &puntato; 

    // If you want to go really crazy you can do things like this:
    int **  ptpti; //- pointer to pointer to int
    int ** const cptpti  = &puntatoreApuntato; // - a const pointer to a pointer to an int
    int * const * ptcpti; // - a pointer to a const pointer to an int
    int const ** ptptci; // - a pointer to a pointer to a const int
    int * const * const cptcpti = &puntatoreApuntato; // - a const pointer to a const pointer to an int
    // ...

    // And to make sure we are clear on the meaning of const

    const int* foo;
    int *const bar = &puntato; //note, you actually need to set the pointer here because you can't change it later ;)
    /*                
    foo is a variable pointer to a constant int. 
    This lets you change what you point to but not the value that you point to. 
    Caso delle stringhe C.

    bar is a const or fixed pointer to a value that can be changed. 
    This is like a reference without the extra syntactic sugar. 
    Because of this fact, usually you would use a reference where you would use a T* const pointer unless you need to allow null pointers.
    */
     
    cout << endl;
    // References
    
    // Modificare variabili dentro le funzioni tramite reference
    int anInt = 0;
    modifyIntByReference( anInt );
    cout << "Prima valeva 0 e adesso " << anInt << " senza usare 'puntatori' " << endl;
    
    // Caso in cui non si usa come argomento
    int notARef = 5;
    int& aRef = notARef;
    aRef += 10;
    cout << "Modificando aRef ho modificato notARef, infatti vale: " << notARef << endl;
    // Questo perche' aRef praticamente E' notARef !!!
    
    cout << endl;
    
    int* pToPass = &notARef;
    cout << pToPass << " -> " << *pToPass << endl;
    modifyPtrByReference(pToPass);
    cout << pToPass << " -> " << *pToPass << endl;
    
    cout << endl << "Giochiamo con array, puntatori e reference" << endl;
    //int a2 [] = { 0, 1, 2, 3}
    int a2 [4]; // Per definire un array sulla stack senza mettere subito l'intero elenco
    a2[0] = 0; a2[1] = 1; a2[2] = 2; a2[3] = 3;
    modifyPtrArray( a2 );
    
    for (auto i = 0; i < 4; i++)
        cout << a2[i] << endl;
        
    int* a3 = new int [4] { 11, 22, 33, 44 };
    modifyPtrArrayByReference( a3 );
    for (auto i = 0; i < 4; i++)
        cout << a3[i] << endl;
        
    delete [] a3;
        
    cout << "Adesso vediamo con l'array di 10 elementi il metodo che accetta solo array di questa grandezza" << endl;
    int a10 [] = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    cycleArrayByPreciseRange( a10 );
    
}



