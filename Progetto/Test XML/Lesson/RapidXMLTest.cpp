#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "lib/rapidxml/rapidxml.hpp"
#include "lib/rapidxml/rapidxml_print.hpp"


using namespace rapidxml;
using namespace std;

int main(void)
{ 
	cout << "Parsing my beer journal..." << endl;
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile ("beerJournal.xml"); 
	// Inseriamo nel vector qui di seguito i char partendo da:
	//				   (iteratore dello stream dal file,    fino all'iteratore che indica l'eof)
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("MyBeerJournal");
	// Iterate over the brewerys
	for (xml_node<> * brewery_node = root_node->first_node("Brewery"); brewery_node; brewery_node = brewery_node->next_sibling())
	{
	    printf("I have visited %s in %s. ", 
	    	brewery_node->first_attribute("name")->value(),
	    	brewery_node->first_attribute("location")->value());
            // Interate over the beers
	    for(xml_node<> * beer_node = brewery_node->first_node("Beer"); beer_node; beer_node = beer_node->next_sibling())
	    {
	    	printf("On %s, I tried their %s which is a %s. ", 
	    		beer_node->first_attribute("dateSampled")->value(),
	    		beer_node->first_attribute("name")->value(), 
	    		beer_node->first_attribute("description")->value());
	    	printf("I gave it the following review: %s", beer_node->value());
	    }
	    cout << endl;
	}
	
	
	// Creiamo un xml
	// Per risolvere i problemi col print di rapidxml leggere: http://stackoverflow.com/questions/14113923/rapidxml-print-header-has-undefined-methods
	cout << "\n\nCreiamo il file\n\n" << endl; 
	xml_document<> wdoc;
	
	xml_node<> *declaration = wdoc.allocate_node( node_declaration);
	declaration->append_attribute(wdoc.allocate_attribute("version","1.0"));
	declaration->append_attribute(wdoc.allocate_attribute("encoding","utf-8"));
	wdoc.append_node(declaration);	
	
	string node_name = wdoc.allocate_string("Root");
	xml_node<> *wroot = wdoc.allocate_node(node_element, node_name.c_str());
	wdoc.append_node( wroot );
	xml_attribute<> *attr = wdoc.allocate_attribute("attrName","attrValue");
	wroot->append_attribute(attr);
	
	xml_node<> *child = wdoc.allocate_node( node_element,  wdoc.allocate_string("Child") );
	wroot->append_node( child );
	attr = wdoc.allocate_attribute("childAttrName","childAttrValue");
	child->append_attribute(attr);
	child->value( wdoc.allocate_string("La stringa dentro il nodo!"));
	  
	cout << wdoc;
	 
	ofstream outfile; 
	outfile.open("MyFile.xml");
	outfile << wdoc;
	outfile.close();
	
	cout << "\n\nLeggiamo ora il file xml" << endl;
	
	ifstream infile;
	infile.open("MyFile.xml");
	string line;
	while ( getline( infile, line ))
	{
		cout << line << endl;
	}
	infile.close();
	
	return 0;
}