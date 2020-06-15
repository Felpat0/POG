#include<iostream>
#include<stdlib.h> 
#include<time.h> 

using namespace std;

void findEven(int *arr, int d);
void swap(int *a, int *b);

namespace POG{
    int finoA;

    void numeriPrimi(){
        int primi[finoA];
        int nTrovati = 0;
        int temp = finoA;
        if(finoA > 0){
            for(int i = 1; i != finoA; i++){
                if(i < 4){
                    primi[nTrovati] = i;
                    nTrovati ++;
                    cout<<i<<"\n";
                }else{
                    bool ok = true;
                    for(int j = 1; j != nTrovati; j++){
                        if(i % primi[j] == 0){
                            ok = false;
                        }
                    }
                    if(ok){
                        primi[nTrovati] = i;
                         nTrovati ++;
                        cout<<i<<"\n";
                    }
                }
            }
        }
    }
}
int main(){
    int n = 0;
    int c = 5;
    int d = 0;
    srand (time(NULL));
/*
    cout<<"Inserisci numero elementi: ";
    cin>>n;

    int *v = new int[n];
    for(int i = 0; i != n; i++){
        v[i] = (rand() %30) + 1;
        cout<<v[i]<<"\n";
    }
    findEven(v, n);
    swap(&c, &d);
    cout<<c<<" "<<d;
    delete v;*/
    cout<<"Inserisci finoA: ";
    cin>>POG::finoA;
    POG::numeriPrimi();
}

void findEven(int *arr, int d){
    int counter = 0;
    for(int i = 0; i != d; i++){
        if(arr[i] % 2 == 0)
            counter ++;
    }
    cout<<"Ci sono "<<counter<<" numeri pari\n";
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}