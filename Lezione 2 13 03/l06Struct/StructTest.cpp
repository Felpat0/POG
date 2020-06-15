#include <iostream>

using namespace std;

struct SimpleCharacter
{
    // di base sono settate su public
    int hp;
    int atk;
    double gold;
         
    SimpleCharacter(int h, int a)
    {
        hp = h;
        atk = a;
        gold = 3;
        cout << "Costruttore classico" << endl;
    }
    
    SimpleCharacter(int h, int a, double g) : hp(h), atk(a), gold(g) 
    {
        cout << "Costruttore ad initialization list" << endl;
    }
}; // <-- occhio al punto e virgola

int main()
{
    SimpleCharacter pg1 = SimpleCharacter(13,3);
    SimpleCharacter pg2 = SimpleCharacter(10,4,10);
    
    cout << "Quale personaggio deve iniziare? (1 = pg1, 2 = pg2) " ;
    int scelta;
    cin >> scelta;
    bool pg1Turn = ( scelta == 2 ) ? false : true; // Qualsiasi caso tranne l'intero 2 fa avere il turno al pg1
        
        
    while ( true ) 
    {
        if ( pg1Turn )
        {
            cout << "pg1 attacca pg2 infliggendo " << pg1.atk << " danni" << endl;
            pg2.hp = ( pg2.hp - pg1.atk > 0 ) ? pg2.hp - pg1.atk : 0;
            cout << "pg2 ha " << pg2.hp << " hp " << endl;
            cout << endl;
            if ( pg2.hp == 0 )
            {
                cout << "Ha vinto il pg1 che guadagna " << pg2.gold << " monete d'oro" << endl;
                pg1.gold += pg2.gold;
                cout << "pg1 ha " << pg1.gold << " monete d'oro " << endl;
                break;
            }
        } 
        else
        {
            cout << "pg2 attacca pg1 infliggendo " << pg2.atk << " danni" << endl;
            pg1.hp = ( pg1.hp - pg2.atk > 0 ) ? pg1.hp - pg2.atk : 0;
            cout << "pg1 ha " << pg1.hp << " hp " << endl;
            cout << endl;
            if ( pg1.hp == 0 )
            {
                cout << "Ha vinto il pg2 che guadagna " << pg1.gold << " monete d'oro" << endl;
                pg2.gold += pg1.gold;
                cout << "pg2 ha " << pg2.gold << " monete d'oro " << endl;
                break;
            }
        }
        
        pg1Turn = !pg1Turn;
    }
    
    cout << " Creiamo tramite puntatore " << endl;
    
    SimpleCharacter* pCharacter = new SimpleCharacter(20,12);
    // Accedo ai suoi campi tramite l'operatore ->
    cout << "HP : " << pCharacter->hp << endl;
    // Oppure dereferenziandolo tra parentesi
    cout << "ATK : " << (*pCharacter).atk << endl;
    
    // E visto che lo instanzio con la parola chiave new DEVO cancellarlo a mano
    delete pCharacter;
    
    return 0;
    
}