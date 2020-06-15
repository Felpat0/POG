#include <iostream>
#include <cstring>

using namespace std;

class Character
{
    // di base sono settate su private
    char* name;
    int hp;
    int atk;
    double gold;
    
    public: // uso i modificatori di accesso seguiti dai due punti e dall'elenco dei membri in tal modo accessibili
    
    Character* enemy;
    int* intDiEsempio;
    
    Character(char* n, int h, int a, double g) : name(n), hp(h), atk(a), gold(g) 
    {
        
        char* p = n;
        int counter = 0;
        for (;*p!=0; ++p) ++counter;

        cout << "size = " << counter << endl;
    	
        name = new char [ counter + 1];
    	/* // Copiando a mano con un ciclo
        p = n;
        for (int i = 0; i < counter; i++ )
            name[i] = n[i];
        name[counter] = '\0';
        */
        
        // Col memcpy
        memcpy( name, n, (counter+1)*sizeof(char) );
        
        cout << "name = " << name << endl;
        intDiEsempio = new int(5);
    }
    
    ~Character()
    {
        
        // Questa parte la fa in automatico
        hp = 0;
        atk = 0;
        gold = 0;
        // Devo invocare il delete sui suoi oggetti legati a puntatori
        
        delete [] name;			// Adesso devo cancellarlo perche' lo inizializzo con la keyword new!
        delete intDiEsempio;    // Devo cancellarlo perche' lo instanzio con la keyword new in questa classe
        enemy = nullptr;        // enemy non viene creato in questa classe, usando il delete potrei
        // distruggere una qualche instanza di Character di cui non voglio (per ora) sbarazzarmi
        
    }
    
    char* getName() { return name; }
    int getHp() { return hp; }
    void addHp( int h ) { hp += h; }
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
    
    (*hero).enemy = badGuy;
    (*hero).attackEnemy();
    
    cout << badGuy->getHp() << endl;
    
    cout << *hero->intDiEsempio << endl; // Come scrivere *(hero->intDiEsempio)
    int* pAllEsempio = hero->intDiEsempio;
    //cout << *pAllEsempio << endl; // Punta alla stessa cella di memoria
    
    delete hero;          
    delete badGuy;        
    
    cout << "di nuovo Hp " << badGuy->getHp() << endl;
    cout << "di nuovo pAllEsempio " << *pAllEsempio << " <-- valore unpredictable perche' e' cancellato " << endl;
    
    return 0; 
}
