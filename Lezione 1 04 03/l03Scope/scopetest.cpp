#include <iostream>
// Una variabile fuori da qualsiasi classe, funzione, namespace e' globale
int globalInt = 20;


// Le variabili interne ad un namespace hanno come scope il namespace stesso
namespace miopropriomio
{
    int namespaceInt = 10;
    

    int func2()
    {
        int i = 0;
    }

    int func3()
    {
        func2();
    }
}

 
// Le variabili dentro una funzione (e i suoi parametri) sono locali
int func( int parameter )
{
    int functionInt = 30;
    parameter += functionInt;
    
    std::cout << "fInt " << functionInt << " parameter " << parameter << "\n\n";
    
    return parameter;
}



using namespace std; // Automaticamente tutti i nomi che non vengono trovati vengono cercati in questo namespace
// Ad esempio cout di base non e' presente in questo file e quindi verra' cercato in std 

int main ()
{
    cout << "globalInt " << globalInt << "\n";
    
    globalInt += 30;
    
    cout << "globalInt " << globalInt << "\n\n";   
    
    cout << "namespaceInt " << miopropriomio::namespaceInt << "\n";
    
    miopropriomio::namespaceInt += 99;
    
    cout << "namespaceInt " << miopropriomio::namespaceInt << "\n\n";
    
    
    int n = 25;
    func( n );
    
    std::cout << n << "\n";
    
}