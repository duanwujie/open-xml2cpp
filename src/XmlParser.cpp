#include <iostream>
#include "XmlParser.h"

using namespace std;

XmlParser::XmlParser()
{
        myDocument = new TiXmlDocument();
}


XmlParser::~XmlParser()
{
        if(myDocument){
                delete  myDocument;
        }
}


void XmlParser::init(string doc)
{
        myDocument->LoadFile(doc.c_str());
}


void XmlParser::DoParser()
{
        root = myDocument->RootElement();
        
        //parser root 
        elemIt = root ;
        //attrIt = elemIt->FirstChildElement();
         

        elemIt = root->FirstChildElement();
        while(elemIt){
                attrIt = elemIt->FirstAttribute();
                while(attrIt){
                        cout<< attrIt->Name()<<" : "<<attrIt->Value()<<endl;
                        attrIt = attrIt->Next();
                }
                

                elemIt = elemIt->NextSiblingElement();
        }
}







