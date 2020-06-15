#include <iostream>

using namespace std;

class Character
{
    // di base sono settate su private
    char* name;
    int hp;
    int atk;
    double gold;
    
    

    public: // uso i modificatori di accesso seguiti dai due punti e dall'elenco dei membri in tal modo accessibili
    
    int* intDiEsempio;
    Character* enemy;
    
    
    Character(char* n, int h, int a, double g) : name(n), hp(h), atk(a), gold(g) 
    {
        intDiEsempio = new int(5);
    }
    
    ~Character()
    {
        
        // Questa parte la fa in automatico
        hp = 0;
        atk = 0;
        gold = 0;
        // Devo invocare il delete sui suoi oggetti legati a puntatori ( che non siano string literal )
        // delete [] name; // <-- NO, perche' gli passo una string literal dal main, in altri casi potrebbe avere senso
        delete intDiEsempio; // Devo cancellarlo perche' lo instanzio con la keyword new in questa classe
        enemy = nullptr; // enemy non viene creato in questa classe, usando il delete potrei
        // distruggere una qualche instanza di Character di cui non voglio (per ora) sbarazzarmi
        
    }
    
    char* getName() 
    { 
        return name; 
    }

    int getHp() { return hp; }
    
    void addHp( int h ) 
    { 
        hp += h; 
    }


    int getAtk() { return atk; }
    double getGold() { return gold; }
    void addGold( double g ) { gold += g; }
    
    void attackEnemy()
    {
        (*enemy).addHp( -atk );
    }
}; // <-- occhio al punto e virgola

int main()
{
    Character* hero = new Character( (char*)"Aragorn",20,4,150);
    Character* badGuy = new Character( (char*)"Uruk-hai", 12,8,25);
    Character* badGuy2 = new Character( (char*)"Pippo", 22,18,50); 

    (*hero).enemy = badGuy;
    (*hero).attackEnemy();
    
    hero->enemy = badGuy2;
    hero->attackEnemy();

    cout << "hp di " << badGuy->getName() << " : " << badGuy->getHp() << endl;
    
    cout << *hero->intDiEsempio << endl; // Come scrivere *(hero->intDiEsempio)
    int* pAllEsempio = hero->intDiEsempio;
    cout << *pAllEsempio << endl; // Punta alla stessa cella di memoria
    
    delete hero;
    delete badGuy;
    delete badGuy2;
    
    cout << "di nuovo Hp del nemico: " << badGuy->getHp() << endl;
    cout << "di nuovo pAllEsempio " << *pAllEsempio << " <-- valore unpredictable perche' e' cancellato " << endl;
    
    return 0;
}