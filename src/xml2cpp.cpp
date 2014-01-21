#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <utility>
using namespace std;
#include "XmlParser.h"
#include "CPPGen.h"
#include "tinyxml.h"


TiXmlElement * g_pRoot=NULL;


int simpleFind(const string * arry,string s,int size)
{
        for(int i=0;i<size;i++){
                if(arry[i] == s)return 1;
        }
        return 0;
}

//it is class member
const string ClassKey[]={
        "works",
        "layer",
        "sub",
        "subsub",
        "resource",
};

const string MemberKey[]={
//        "resource",
};


class xmlItem{
public:
        string key;
        string name;
        string value;
        int    level;
        xmlItem(string key,string name,string value,int level){
                this->name = name;
                this->value = value;
                this->key = key;
                this->level = level;
        }

};


vector<xmlItem *>  iv;

deque<xmlItem *>  dv;

deque<int> dep;




list<TiXmlElement *> pparent;


bool ParseXmlText(TiXmlElement* pEleRoot,int level)
{
    if (NULL == pEleRoot)
    {
        return false;
    }
    TiXmlElement* pEle = NULL;


    bool theone=true;
    for (pEle = pEleRoot->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
    {
        if(theone){
                theone = false;
                level++;
        }
        TiXmlAttribute* attr = pEle->FirstAttribute();  //获得student的name属性
        xmlItem * temp = new xmlItem(pEle->Value(),attr->Name(),attr->Value(),level);

        dv.push_back(temp);
        //cout<<pEle->Value()<<"::";

        TiXmlAttribute* first = attr;

        attr = attr->Next();

        //TiXmlNode *parent = pEle->Parent();

        

        while (attr) {
                xmlItem * temp1 = new xmlItem("NULL",attr->Name(),attr->Value(),level);
                dv.push_back(temp1);
                attr = attr->Next();
        }
        ParseXmlText(pEle,level);
        

        
        //cout << endl;
    }


    return true;
}

bool ConfigToCpp(TiXmlElement* pEleRoot,SimpleGen * mgen)
{
    if (NULL == pEleRoot)
    {
        return false;
    }
    TiXmlElement* pEle = NULL;

    for (pEle = pEleRoot->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
    {
        TiXmlAttribute* attr = pEle->FirstAttribute();  //获得student的name属性
        TiXmlAttribute* first = attr;
        attr = attr->Next();


        while (attr) {
                TiXmlElement * p = pEle;
                while(p!=g_pRoot){
                        pparent.push_back(p);
                        p=p->Parent()->ToElement();
                }
                //pparent.push_back(g_pRoot);

                mgen->out<<"const string ";
                mgen->out<<g_pRoot->Value()<<"::";
                while(!pparent.empty()){
                        TiXmlElement * cur = pparent.back();
                        TiXmlAttribute * cat = cur->FirstAttribute();
                        mgen->out<<cur->Value()<<"_"<<cat->Name()<<"_"<<cat->Value()<<"::";
                        pparent.pop_back();
                }
                
                mgen->out<<attr->Name()<<" = "<<"\""<<attr->Value()<<"\" ;"<<endl;
                attr = attr->Next();
        }
        ConfigToCpp(pEle,mgen);
    }
    return true;
}

int ConfigToH(TiXmlElement * pRoot)
{

        //Create file 
        string hfile=pRoot->Value();
        hfile+=".h";
        
        SimpleGen h(hfile);

        /*  生成root类 */
        h.genPretreatment(pRoot->Value());
        h.genIncludeNeed("iostream");
        h.genNamespace("std");
        h.genClass(pRoot->Value());
        TiXmlAttribute * attri = pRoot->FirstAttribute();
        while(attri){
                h.genMember("string",attri->Name(),1);
                attri = attri->Next();
        }
        int current_class_level=0;
        int pre_level = 0;

                        

        while(!dv.empty()){
                xmlItem * the = dv.front();
 
                if(!dep.empty()){
                        pre_level = dep.back();
                }



                //Gernerate the class begin
                if(simpleFind(ClassKey,the->key,sizeof(ClassKey)/sizeof(string))){
                        string cid = the->key+"_"+the->name+"_"+the->value;
                        //dep.push_back(the->level);

                        //Get the press level
#ifdef _DEBUG
                        cout<<"pre:"<<pre_level<<","<<"the:"<<the->level<<endl;
#endif
                        if(the->level > pre_level){
                                //该类属于上一层次的子类,因此上一层的类并没有处理完
                                dep.push_back(the->level);
                        }
                        else if(the->level == pre_level){
                                //处理完同一级的类了
                                //dep.push_back(the->level);
                                //h.genNamespace("dddd");
                                h.genClassEnd(the->level);
                        }
                        else if(the->level < pre_level){

                                for(int k=pre_level;k>=the->level;k--){
                                        h.genClassEnd(k);
                                        dep.pop_back();
                                }
                                //h.genNamespace("test");
                                dep.push_back(the->level);


                                //当前类处理完了
                        }
                        h.genClass(cid,the->level);

                }


               
                if("NULL" == the->key && the->level == pre_level){
                        h.genMember("string",the->name,the->level + 1);
                }

                if(simpleFind(MemberKey,the->key,sizeof(MemberKey)/sizeof(string))){
                        string mid = the->key+"_"+the->name+"_"+the->value;
                        h.genMember("string",mid,the->level);
                }

                //cout<<the->key<<" "<<the->name<<" "<<the->value<<" "<<the->level<<endl;
                //cout<<the->key+"_"+the->name+"_"+the->value<<"\t"<<the->level<<endl;
                delete the;
                dv.pop_front();
        }

        //All closed gen {
        while(!dep.empty()){
                current_class_level = dep.back();
                h.genClassEnd(current_class_level);
                dep.pop_back();
        }
        h.genClassEnd();
        h.genPretreatmentEnd();
}


int main()
{

	TiXmlDocument aDoc("test.xml");
	if ( ! aDoc.LoadFile() )
	{
		perror("打开test.xml失败:");
		return -1;
	}

	TiXmlElement *pRoot = aDoc.RootElement();
	TiXmlElement *pWork = pRoot;

        g_pRoot = pRoot;
        string cfile=pRoot->Value();
        string hfile=pRoot->Value();
        hfile+=".h";
        cfile+=".cpp";
        SimpleGen c(cfile);
        c.genIncludeNeed(hfile);
        
        ConfigToCpp(pWork,&c);

        ParseXmlText(pWork,0);
        ConfigToH(pWork);
}

