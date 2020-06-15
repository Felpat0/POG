#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "lib/rapidxml/rapidxml.hpp"
#include "lib/rapidxml/rapidxml_print.hpp"


using namespace rapidxml;
using namespace std;

void initXMLDocument(){
    xml_document<> doc;
	xml_node<> * root_node;

    ifstream theFile ("test.xml"); 

    //Indicate start and end of the stream
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    //Add the "end file character" at the end of the file
	buffer.push_back('\0');
	//Parse the buffer using the xml file parsing library into doc, now the xml_document is ready
	doc.parse<0>(&buffer[0]);
	//Assign the root node to root_node (the method returns and address)
	root_node = doc.first_node("Game");
    root_node = root_node->first_node("Rooms");
    for (xml_node<> * roomNode = root_node->first_node("Room"); roomNode; roomNode = roomNode->next_sibling())
	{
	    printf("I have visited %s. ", 
	    	roomNode->first_attribute("label")->value());
        //Interate over the doors
	    for(xml_node<> * doorNode = roomNode->first_node("Door"); doorNode; doorNode = doorNode->next_sibling())
	    {
	    	printf("The door of %s was %s", 
	    		doorNode->first_attribute("room")->value(),
	    		doorNode->first_attribute("locked")->value());
	    }
	    cout << endl;
	}
}



int main(){
    initXMLDocument();
}