#ifndef __CPPGEN_H_
#define __CPPGEN_H_

#include <iostream>
#include <fstream>
using namespace std;

#define G_CLASS_B(className) ("class " + className + "{" + "\n")

#define G_PUBLIC_B() ("public:\n")

#define G_CLASS_E() ("};\n\n")

#define G_MEMBER(type,name)("static const " + type + " " + name + ";\n")

#define G_PRETREATMENT(className) \
        ("#ifndef __"+className+"_h_\n"+\
        "#define __"+className+"_h_\n")
#define G_PRETREATMENT_E() ("#endif\n")

#define G_INITMEMBER(domin,value,type) ("static const "+ type +" "+ domin +" = " +value+"\n")

#define G_INCLUDE(inc) ("#include" "\"" + inc +"\"\n")

#define G_NAMESPACE(space) ("using namespace "+space + ";\n")




class SimpleGen
{
        void inline levelFormat(int level);
public:
        ofstream  out;
        //SimpleGen(string filename);
        SimpleGen(string filename):out(filename.c_str(),ofstream::out|ofstream::trunc){}
        ~SimpleGen();

        /* class gen function */
        void genClass(string className,int level = 0);
        void genClassEnd(int level = 0);

        /*  member gen function  */
        void genMember(string type,string name,int level = 0);

        void genPretreatment(string className,int level = 0);
        void genPretreatmentEnd(int level = 0);
        void genInitMember(string domin,string value,int level = 0);
        void genIncludeNeed(string inc, int level = 0);
        void genNamespace(string space, int levle = 0);
 
};



class layer_id_1 {
public:
       static const string resource_id_1;
       static const string resource_id_2;
       static const string resource_id_3;
       static const string resource_id_4;
       static const string resource_id_5;
       class sub_id_1{
       public:
               static const string resource_id_1;
       };
               
};


//const string layer_id_1::sub_id_1::resource_id_1="/home/test";

#endif
