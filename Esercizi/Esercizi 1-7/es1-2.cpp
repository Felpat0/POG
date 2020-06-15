#include<iostream>
#include <stdlib.h> 
#include <time.h> 

using namespace std;
int v[10];
void computeMinMax(int *v, int d);

int main(){
    int min = 30;
    int max = 0;

    srand (time(NULL));

    for(int i = 0; i != 10; i++){
        v[i] = (rand() %30) + 1;
        //cout<<v[i]<<"\n";
        if(i>0){
            if(v[i] < min)
                min = v[i];
            else if(v[i] > max)
                max = v[i];
        }
    }
    computeMinMax(v, 10);
    //cout<<"Il minimo e' "<<min<<"\nIl massimo e' "<<max;
}

void computeMinMax(int *arr, int d){
    int min = 30;
    int max = 0;

    for(int i = 0; i != d; i++){
        cout<<arr[i]<<"\n";
         if(arr[i] < min)
            min = v[i];
         else if(arr[i] > max)
            max = v[i];
    }

    cout<<"Il minimo e' "<<min<<"\nIl massimo e' "<<max;
}