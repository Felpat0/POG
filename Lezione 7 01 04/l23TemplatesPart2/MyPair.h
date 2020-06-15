#include <iostream>
#include <string>

using namespace std;

template <class T> 
class MyPair
{
	string label;
    T a, b;
    
    public:
        MyPair()
        {
           a = b = 0;
		   label = "MyPair";
        }
        
        MyPair(const T& _a,const T& _b) 
        : a(_a), b(_b) 
		{
			label = "MyPair";
		}
		
		MyPair(const T& _a,const T& _b, string s)
        : a(_a), b(_b), label(s) {}
        
        template<class paramT> 
        MyPair<T> operator*=(paramT c)
        {
            std::cout << "\nOperator * che restituisce MyPair<T>";
			a *= c;
			b *= c;
            return *this;
        }
                
        //WARNING: with this declation you return the same type of the instantiated object
        /*EXAMPLE: if you had instatiated 
                MyPair<int> intPair(a,b)  
                MyPair<double> doublePair(_a,_b)

         * If you do  intPair    + 	doublePair 	you will take a int pair
         * If you do  doublePair + 	intPair 	you will take a double pair
        */ 
        template<class paramT> 
        MyPair<T> operator+( MyPair<paramT> &v) 
        {
            std::cout << "\n\nOperator + che restituisce un MyPair del tipo del primo membro";
            return MyPair<T>( this->a + v.getA() , this->b + v.getB() );

        }

		// MyPair<int> myI, MyPair<float> myF, MyPair<double> myDouble
        // myDouble = myI + myF;
		template<typename returnT, class paramT> 
        MyPair<returnT> sum( MyPair<paramT> &v) 
        {
            std::cout << "\n\nsum";
            return MyPair<returnT>( this->a + v.getA() , this->b + v.getB() );
        }
		
		template<typename t1, typename t2>
		void prova(t1 val1, t2 val2 )
		{
			cout << " Prova : " << val1 << " " << val2 << endl;
		}
                 
        // I metodi get restituiscono il tipo T
        T getA() { return a; }

        T getB() { return b; }
        // I metodi set prendono in input il tipo T
        void setA(T _a) { a = _a;  }
        
        void setB(T _b) { b = _b;  }
        
        void print(){
            std::cout << "\t " << label << " {" << a << " , " << b << "} ;" << std::endl ;
        }
    
};