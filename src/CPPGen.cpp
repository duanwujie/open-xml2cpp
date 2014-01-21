#include "CPPGen.h"


//SimpleGen::SimpleGen(string filename):out(filename,ofstream::out|fstream::in|ofstream::trunc)
//{
//}


SimpleGen::~SimpleGen()
{

}


void inline SimpleGen::levelFormat(int level)
{
        while(level--)out<<"\t";
}


void SimpleGen::genPretreatment(string className,int level)
{
        //Turn to big
        levelFormat(level);
        out<<G_PRETREATMENT(className);
}

void SimpleGen::genPretreatmentEnd(int level)
{
        levelFormat(level);
        out<<G_PRETREATMENT_E();
}

void SimpleGen::genClass(string className,int level)
{
        levelFormat(level);
        out<<G_CLASS_B(className);
        levelFormat(level);
        out<<G_PUBLIC_B();
}

void SimpleGen::genMember(string type,string name,int level)
{
        levelFormat(level);
        out<<G_MEMBER(type,name);
}

void SimpleGen::genClassEnd(int level)
{
        levelFormat(level);
        out<<G_CLASS_E();
}

void SimpleGen::genInitMember(string domin,string value, int level)
{
        
        levelFormat(level);
        string T="string";
        G_INITMEMBER(domin,value,T);
}

void SimpleGen::genIncludeNeed(string inc,int level)
{
        levelFormat(level);
        out<<G_INCLUDE(inc);
}

void SimpleGen::genNamespace(string space,int level)
{
        levelFormat(level);
        out<<G_NAMESPACE(space);
}

/*
 * 
 *  template
 */





const string layer_id_1::resource_id_1 = "/home/test";
const string layer_id_1::resource_id_2 = "/home/test";
const string layer_id_1::resource_id_3 = "/home/test";
const string layer_id_1::resource_id_4 = "/home/test";
const string layer_id_1::resource_id_5 = "/home/test";


