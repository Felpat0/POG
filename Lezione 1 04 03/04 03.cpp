#include <iostream>


void somma(int *value, int summedBy){
	*value += summedBy;
}

int main(){
	int cane;
	std::cout<<"Inserisci un numero: \n";
	std::cin>>cane;
	std::cout<<"\nHai digitato: "<<cane;
	
	int v[3] = {1, 2, 3};
	
	for (int i = 0; i != 3; i++){
		std::cout<<"\n"<<v[i];
	}
	
	int *p;
	p = &cane;
	
	std::cout<<"\nIl puntatore punta il valore:"<<*p;
	std::cout<<"\nL'indirizzo puntato e' "<<p;
	std::cout<<"\nL'indirizzo del puntatore e' "<<&p;
	std::cout<<"\nGia', sono uguali, complimenti, intelligentissimo.";
	
	//Per spostare il puntatore in termini di cella di memoria:
	p++;
	
	//String as char array (last element is /0 -> end of the array)
	//NB: gli elementi dell'array sono adiacenti in termini di memoria
	char s[5] = "cane";
	std::cout<<"\n"<<s;
	
	char *q;
	//Comandi equivalenti:
	q = s;
	q = &s[0];
	
	//Comandi DIFFERENTI:
	*(++q); //Sposta il puntatore
	*(q++); //Incrementa il contenuto
	
	std::cout<<q++; //Prima restituisce (stampa) poi incrementa
	std::cout<<++q; //Prima modifica l'elemento, poi lo restituisce (stampa)
	
	int a = 5;
	somma(&a, 10);
	
	std::cout<<"\n"<<a;
	return 0;
}
