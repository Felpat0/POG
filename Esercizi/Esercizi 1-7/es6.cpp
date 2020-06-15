#include<iostream>

using namespace std;

void printEven(int *arr, int d);
int* updateArray(int *arr, int d, int newD);

int main(){
    int n;
    cout<<"Inserisci la dimensione dell'array: ";
    cin>>n;

    int *v = new int[n];
    for(int i = 0; i != n; i++){
        v[i] = i;
    }

    printEven(v, n);
    int newD;
    cout<<"Inserisci la NUOVA dimensione dell'array:\n";
    cin>>newD;
    v = updateArray(v, n, newD);
    cout<<"\n\nNuovo array:";
    for(int i = 0; i != newD; i++){
        cout<<v[i]<<endl;
    }
}

void printEven(int *arr, int d){
    int counter = 0;
    for(int i = 0; i != d; i++){
        cout<<arr[i]<<endl;
        if(arr[i] % 2 == 0)
            counter ++;
    }
    cout<<"Ci sono "<<counter<<" numeri pari\n";
}

int* updateArray(int *arr, int d, int newD){

    if(newD == d){
        return arr;
    }else if(newD > d){
        int *temp = new int[newD];
        for(int i = 0; i != newD; i++){
            if(i < d){
                temp[i] = i;
            }else{
                temp[i] = i*2;
            }
        }
        return temp;
    }else{
        int *temp = new int[newD];
        for(int i = 0; i != newD; i++){
            temp[i] = i;
        }
        return temp;

    }

}