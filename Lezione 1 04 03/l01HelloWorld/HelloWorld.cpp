#include <iostream>

/* Un paio di contatti


[ STM - POG 2019 - 2020 ]

 fabrizio.bazzurri@gmail.com
 jacopo.zuliani.dev@gmail.com

*/

// Per compilare da terminale un file unico:
// g++ -c -g -std=c++11 NomeFile.cpp

int main ()
{
    std::cout << "Hello World\n";
    
    // Commento in riga
    /*
        Blocco di commenti
    */
    
    int i1 = 4;
    int i2 {8};
    int i3 = {15};
    
    double d1 {16.23};
    
    float f1 = 42.0f;
    
    bool booleana = true;
    
    char carattere = 'a';
    
    std::cout << i1 << " " << i2 << " " << i3 << " " << d1 << " " << f1 << "\n";
    std::cout << "bool = " << booleana << " char = " << carattere << "\n";
    
    
    int iArray [5] = { 2, 4, 8, 16, 32 };
    for (auto i = 0; i < 5; i++ )
    {
        std::cout << " " << iArray[i];
    }
    std::cout << "\n";
    
    
    
    
}