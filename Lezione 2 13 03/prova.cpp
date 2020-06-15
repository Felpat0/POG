#include<iostream>

void f(int* &pArr){
    //arr e pArr qui sono la stessa identica cosa, anche in indirizzo
    pArr[1] = 2;
    //Se faccio
    pArr++;
    //L'array ora inizia dal secondo elemento (gli ho spostato l'indirizzo di memoria)
}

int main(){
    using namespace std;
    int v[] = {1, 3 ,5};
    for(auto i : v){
        cout<<"ciao";
    }

    int *arr = new int[3];
    f(arr);
}