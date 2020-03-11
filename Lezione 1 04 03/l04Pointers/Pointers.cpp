#include <iostream>


using namespace std;

void moltiplicaPer( int* a, int* b, int multiplier)
{
    *a *= multiplier;
    *b *= multiplier;

    a = b;
}


int main ()
{
    
    int a = 5;
    // &a = l'indirizzo di memoria della variabile a
    // int* p = dichiaro un puntatore a int 
    int * p;
    p = &a;
    *p += 2;

    int b = a;
    b += 1;
    p = &b;
    *p = 12;
    
    cout << p << " " << &b << "\n";
    
    cout << *p << " " << a << " " << b << "\n"; 
    
    int c = 8;
    p = &c;
    *p += 7;
    
    cout << *p << " " << c ;
    
    
    char v[6] = "Hello"; // l'ultimo elemento e' automaticamente -> '\0'
    
    std::cout << "\n" << v << "\n";
   
    char* pc;
    
    pc = &v[4];
    
    *pc = ' ';
    
    std::cout << v << "\n";
    
    
    
    pc = &v[1];
    *pc = 'a';
    pc++;
    pc++;
    *pc = 'o';
    
    cout << v << "\n" ;
    
    int intero = 0;
    cout << intero++ << "\n"; // 0 ( intero++ prima restituisce il valore e poi incrementa la variabile)
    cout << intero << "\n";   // 1
    cout << ++intero << "\n"; // 2 ( ++intero prima incrementa la variabile e poi restituisce il valore)

    *(++pc) = 't';
    *pc = 'a';
    cout << v << "\n";
    
    
    int n1 = 3;
    int n2 = 5;
    
    int* pn1 = &n1;
    int* pn2 = &n2;

    cout << "n1 " << n1 << " n2 " << n2 << "\n";
    cout << "pn1 " << pn1 << " pn2 " << pn2 << "\n";

    moltiplicaPer(pn1, pn2, 3);
    
    cout << "n1 " << n1 << " n2 " << n2 << "\n";
    cout << "pn1 " << pn1 << " pn2 " << pn2 << "\n";
    
    int* pntmp;
    pntmp = pn1;
    pn1 = pn2;
    pn2 = pntmp;
    
    moltiplicaPer(pn1, pn2, 3);
    
    cout << "n1 " << n1 << " n2 " << n2 << "\n";
    
    int numero = 10;
    int* pn = &numero;
    int** ppn = &pn;
    
    cout << numero << "\n";
    // Per modificare "numero" devo dereferenziare due volte
    **ppn = 15;
    cout << numero << "\n";

    
    int altroNumero = 99;
    // Per modificare il puntatore di mezzo, dereferenzio una volta sola
    *ppn = &altroNumero;
    cout << numero << " " << **ppn << "\n";
    
    ppn = nullptr; // Il valore nullo per un puntatore 
    
    int intArray [5] = { 1, 2, 3, 4, 5 };
    cout << intArray[3] << "\n";
    
    // La parola chiave new alloca uno spazio di memoria nella heap
    // per poterla gestire e' necessario utilizzare i puntatori
    // Per gli array questo e' l'unico modo di avere una dimensione dipendente da variabili
    int dim = 15;
    double* intArrayPtr = new double[dim];

    for (int i = 0; i < dim; i++)
    {
        if ( i % 2 == 0 && i % 3 == 0 )
        {
            intArrayPtr[i] = 6;
        }
        else if ( i % 2 == 0 )
        {
            intArrayPtr[i] = 2;
        }
        else if ( i % 3 == 0 )
        {
            intArrayPtr[i] = 3;
        }
        else
            intArrayPtr[i] = 1;
         
        cout << intArrayPtr[i] << " ";
    }
     
    // Per liberare la memoria allocata nella heap dovete utilizzare la keyword delete
    // la regola base e': per ogni "new" dovete mettere un "delete"
    // altrimenti quella porzione di memoria restera' occupata fino al riavvio del computer 
    // (o finche' non crasha)
    delete [] intArrayPtr;
    
    // Vediamo il caso di una variabile singola e non di un array
    int *intInTheHep = new int(1989);

    cout << "\n" << (*intInTheHep) << " in indirizzo di memoria " << intInTheHep << "\n";

    delete intInTheHep;
    /*
    */ 
    return 0;
}



