#include<iostream>
#include<map>
#include<string>
#include<algorithm>
#include "instset.h"
using namespace std;
map< string,list<string> > progmap;
void eval_inst(string arr[],reg_state & ob){
    map<string, list<string> >::iterator it3;
    string val,src,des;
    val=src=des="";
    list<string>::iterator it4;
    if(arr[0]=="LDA"){
       // cout<<arr[0]<<", "<<arr[1];
        //rarr[in++]=arr[1];
        it3=progmap.find(arr[1]);
        it4=it3->second.begin();
        val=*it4;
        //cout<<val;
        LDA(val,ob);
    }
    else if(arr[0]=="LDAX"){
        if(arr[1]=="B"){
            src=valofBC(ob);
        }
        else if(arr[1]=="D"){
            src=valofDE(ob);
        }
        else if(arr[1]=="H"){
            src=valofHL(ob);
        }
        it3=progmap.find(src);
        it4=it3->second.begin();
        val=*it4;
        LDA(val,ob);
    }
    else if(arr[0]=="LXI"){
        //rarr[in++]=arr[2];
        des=arr[1].substr(0,1);
        LXI(des,arr[2],ob);
    }
    else if(arr[0]=="LHLD"){
        it3=progmap.find(arr[1]);
        it4=it3->second.begin();
        val=*it4;
        int v1;
        stringstream sa,sm;
        sm << hex << arr[1];
        sm >> v1;
        sa << hex << (++v1);
        src=sa.str();
        transform(src.begin(),src.end(),src.begin(), ::toupper);
        it3=progmap.find(src);
        it4=it3->second.begin();
        string val1=*it4;
        //cout<<"second string"<<val1;
        LHLD(val,val1,ob);
    }
    else if(arr[0]=="STA"){
        //rarr[in++]=arr[1];
        string res=STA(ob);
        progmap[arr[1]].push_back(res);
    }
    else if(arr[0]=="STAX"){
        val=STA(ob);
        if(arr[1]=="B"){
            des=valofBC(ob);
        }
        else if(arr[1]=="D"){
            des=valofDE(ob);
        }
        else if(arr[1]=="H"){
            des=valofHL(ob);
        }
        //rarr[in++]=des;
        progmap[des].push_back(val);
    }
    else if(arr[0]=="SHLD"){
        val=valofHL(ob);
        string x=val.substr(0,2);
        string y=val.substr(2,2);
        //rarr[in++]=arr[1];
        progmap[arr[1]].push_back(x);
        int num;
        stringstream sa,sm;
        sm << hex << arr[1];
        sm >> num;
        sa << hex << (++num);
        src=sa.str();
        transform(src.begin(),src.end(),src.begin(), ::toupper);
        //cout<<endl<<"string is"<<endl;
        //rarr[in++]=src;
        progmap[src].push_back(y);
    }
    else if(arr[0]=="ADD"){
        if(arr[1]=="M"){
            src=valofHL(ob);
            it3=progmap.find(src);
            it4=it3->second.end();
            it4--;
            val=it4->back();
            ADD(val,ob,1);
        }
        else{
            ADD(arr[1],ob,2);
        }
    }
    else if(arr[0]=="ADI"){
        ADI(arr[1],ob);
    }
    else if(arr[0]=="ADC"){
        if(arr[1]=="M"){
            src=valofHL(ob);
            it3=progmap.find(src);
            it4=it3->second.begin();
            val=*it4;
            ADC(val,ob,1);
        }
        else{
            ADC(arr[1],ob,2);
        }
    }
    else if(arr[0]=="SUB"){
        if(arr[1]=="M"){
            src=valofHL(ob);
            it3=progmap.find(src);
            it4=it3->second.begin();
            val=*it4;
            SUB(val,ob,1);
        }
        else{
            SUB(arr[1],ob,2);
        }
    }
    else if(arr[0]=="SUI"){
        SUI(arr[1],ob);
    }
    else if(arr[0]=="SBB"){
        if(arr[1]=="M"){
            src=valofHL(ob);
            it3=progmap.find(src);
            it4=it3->second.begin();
            val=*it4;
            SBB(val,ob,1);
        }
        else{
            SBB(arr[1],ob,2);
        }
    }
    else if(arr[0]=="MOV"){
        if(arr[1][0]=='M'){
            des=valofHL(ob);
            //rarr[in++]=des;
            progmap[des].push_back(MOV(arr[1],arr[2],ob,1));
        }
        else if(arr[2]=="M"){
            src=valofHL(ob);
            it3=progmap.find(src);
            it4=it3->second.end();
            it4--;
            val=it4->back();
            //cout<<val;
            des=arr[1].substr(0,1);
            MOV(des,val,ob,2);
        }
        else{
            des=arr[1].substr(0,1);
            MOV(des,arr[2],ob,3);
        }
    }
    else if(arr[0]=="MVI"){
        if(arr[1][0]=='M'){
                des=valofHL(ob);
                //rarr[in++]=des;
                progmap[des].push_back(arr[2]);

        }
        else{
            des=arr[1].substr(0,1);
            src=arr[2].substr(0,2);
            MVI(des,src,ob);
        }
    }
    else if(arr[0]=="INR"){
        INR(arr[1],ob);
        }
    else if(arr[0]=="DCR"){
        DCR(arr[1],ob);
    }
    else if(arr[0]=="INX"){
        if(arr[1]=="B"){
            val=valofBC(ob);
        }
        else if(arr[1]=="D"){
            val=valofDE(ob);
        }
        else if(arr[1]=="H"){
            val=valofHL(ob);
        }
        INX(arr[1],val,ob);
    }
    else if(arr[0]=="DCX"){
        if(arr[1]=="B"){
            val=valofBC(ob);
        }
        else if(arr[1]=="D"){
            val=valofDE(ob);
        }
        else if(arr[1]=="H"){
            val=valofHL(ob);
        }
        DCX(arr[1],val,ob);
    }
    else if(arr[0]=="CMP"){
        if(arr[1]=="M"){
            src=valofHL(ob);
            it3=progmap.find(src);
            it4=it3->second.begin();
            val=*it4;
            CMP(val,ob,1);
        }
        else
            CMP(arr[1],ob,2);
    }
}

map< string, list<string> >::iterator jmp_ins(string arr[], reg_state &ob){
    string src=arr[1];
    map<string, list<string> >::iterator it3;
    if(arr[0]=="JMP"){
        it3=progmap.find(src);
        return (it3--);
    }
    else if(arr[0]=="JC"){
        if(ob.CY==true){
            it3=progmap.find(src);
            it3--;
        }
        else
            it3=progmap.find(ob.PC);
        return it3;
    }
     else if(arr[0]=="JZ"){
        if(JZ(ob)){
            cout<<"now zero"<<lastdec<<endl;
            it3=progmap.find(src);
            it3--;
        }
        else
            it3=progmap.find(ob.PC);
        return it3;
    }

    else if(arr[0]=="JNC"){
        if(ob.CY==false){
            it3=progmap.find(src);
            it3--;
        }
        else
            it3=progmap.find(ob.PC);
        return it3;
    }
    else if(arr[0]=="JNZ"){
        if(JNZ(ob)){
            it3=progmap.find(src);
            it3--;
        }
        else
            it3=progmap.find(ob.PC);
        return it3;
    }
}

int check_ins(string str){
    if(str=="MVI"||str=="ADI"||str=="SUI")
        return 2;
    else if(str=="LXI"||str=="LHLD"||str=="SHLD"||str=="LDA"||str=="STA"||str=="JMP"||str=="JC"||str=="JNC"||str=="JZ"||str=="JNZ")
        return 3;
    else
        return 1;
}

