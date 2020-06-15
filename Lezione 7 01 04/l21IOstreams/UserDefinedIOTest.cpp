#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits> // <- per usare numeric_limits<>


using namespace std;

struct Entry
{
	string name;
	int number;	
};
// cout << entry;
ostream& operator<<(ostream& os, const Entry& e)
{
	return os << "{\"" << e.name << "\", " << e.number << "}";
}

// Leggera':  {"name",number} 
istream& operator>>(istream& is, Entry& e)
{
	char c, c2;
	if (is>>c && c=='{' && is>>c2 && c2=='"' ) // Inizia con: {" 
	{
		string name;
		while (is.get(c) && c!='"') // Fine del nome con: " 
			name+=c;
		
		if (is>>c && c==',') 
		{
			int number = 0;
			if (is>>number>>c && c=='}' ) // Il numero e' seguito da: }
			{
				//e = {name,number};
				e.name = name;
				e.number = number;
				return is;
			}
		}
	}
	is.setstate(ios_base::failbit);
	return is;
}

int main(void)
{
	Entry inEntry;
	if ( cin >> inEntry)
	{
		cout << inEntry;
	}
	else
	{
		cout << "Formattazione errata!" << endl;
	}
	
	
	return 0;
}