/*Creare una classe Float2 che rappresenti un vettore bidimensionale di numeri float.
Fare l'overload di tutti gli operatori ( vettore + vettore, vettore + scalare, vettore + scalare,...)
implementare anche prodotti scalari/vettoriali/normalizzazione...
Testare tutti gli operatori in un main a parte.*/
#include<iostream>
#include <math.h>

class Float2D{
    float x;
    float y;
    public:
    Float2D(float a, float b) : x(a), y(b){}

    Float2D operator+(Float2D other){
        return Float2D(x + other.x, y + other.y);
    }

    Float2D operator-(Float2D other){
        return Float2D(x - other.x, y - other.y);
    }

    Float2D operator*(float other){
        return Float2D(x * other, y * other);
    }

    Float2D operator/(float other){
        return Float2D(x / other, y / other);
    }

    float operator*(Float2D other){
        return (x * other.x) + (y * other.y); 
    }

    inline const float& getX() const {return x;}
    inline const float& getY() const {return y;}

    void normalize(){
        float temp = sqrt(pow(x, 2) + pow(y, 2));
        x = x/temp;
        y = y/temp;
        std::cout<<"\n"<<temp<<"\n";
    }
};

int main(){
    Float2D a(1, 2);
    Float2D b(10, 10);
    std::cout<<"Prodotto scalare: "<<a*b;
    a = a + b;
    std::cout<<"\nX = "<<a.getX()<<"\nY = "<<a.getY();
    a.normalize();
    std::cout<<"\n a normalizzato: " <<"\nX = "<<a.getX()<<"\nY = "<<a.getY();
}