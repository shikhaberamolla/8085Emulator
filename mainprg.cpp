#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<list>
#include<map>
#include<sstream>
#include "reg.h"
#include "mapfunc.h"

void showresult(map<string, list<string> >::iterator);
using namespace std;
int main()
{
    string line, arr[4], word;
    string add,ins;
    int endofprg=0,i,v1,v2;
    ifstream file;
    file.open("abc.txt");
    getline(file,line);
    stringstream s(line);
    s >> add;
    while(getline(file,line)){
        stringstream ss(line);
        //ss >> add;
        ss >> ins;
        progmap[add].push_back(ins);
        while(ss >> word){
            //cout<<word<<" ";
            progmap[add].push_back(word);
        }
        //cout<<"ADDress "<<add<<endl;
        v1=check_ins(ins);
        stringstream sa,sb;
        sa << hex << add;
        sa >> v2;
        sb <<hex << (v2+v1);
        add=sb.str();
        transform(add.begin(),add.end(),add.begin(), ::toupper);
        //cout<<add<<endl;
    }
    reg_state obj;
    for(map< string,list<string> >::iterator it1=progmap.begin();it1!=progmap.end();it1++){
        obj.PC=(it1->first);
        cout<<it1->first;
        int i=0;
        for(list<string>::iterator it2=it1->second.begin();it2!=it1->second.end();it2++){
            if(*it2=="HLT"){
                endofprg=1;
            }
            arr[i++]=*it2;
            cout<<*it2<<" ";
        }
        cout<<endl;
        if(endofprg){
            cout<<endl<<"CONTENTS OF MEMORY"<<endl;
            showresult(++it1);
            break;
        }
        if(arr[0][0]=='J'){
            it1=jmp_ins(arr,obj);
            //cout<<"value of iterator "<<it1->first;
            continue;
        }
        eval_inst(arr,obj);
        //cout<<endl;
        }
        cout<<endl<<"STATE OF REGISTERS"<<endl;
        obj.show_state();

}

void showresult(map<string, list<string> >::iterator it1)
{
    map<string, list<string> >::iterator it3;
    list<string>::iterator it4;
    string res;
    for(it3=it1;it3!=progmap.end();it3++){
            cout<<it3->first<<" ";
            it4=it3->second.end();
            it4--;
        //for(it4=it3->second.begin();it4!=it3->second.end();it4++){
            res=it4->back();
            if(res.size()==1)
                res="0"+res;
            cout<<res<" ";
        //}
        cout<<endl;
    }
}
