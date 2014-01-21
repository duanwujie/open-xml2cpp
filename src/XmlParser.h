#ifndef __XMLPARSER_H_
#define __XMLPARSER_H_


#include <iostream>
#include <vector>
using namespace std;
#include "tinyxml.h"

class XmlParser
{
        TiXmlDocument * myDocument;
        TiXmlElement * root;
        TiXmlElement * elemIt;
        TiXmlAttribute * attrIt;
public:
        XmlParser();
        ~XmlParser();
        void init(string doc);
        void DoParser();
        vector<TiXmlElement *> vele1;
};

#endif
