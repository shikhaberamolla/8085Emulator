#include<string>
#include<sstream>
#include<algorithm>
string lastdec="";
string valofHL(reg_state & ob)
{
    return(ob.H+ob.L);
}

string valofBC(reg_state & ob)
{
    return(ob.B+ob.C);
}

string valofDE(reg_state & ob)
{
    return(ob.D+ob.E);
}

void LDA(string val, reg_state & ob)
{
    ob.A=val;
    return;
}

void LXI(string des,string val,reg_state & ob)
{
    string x=val.substr(0,2);
    string y=val.substr(2,2);
    if(des=="H"){
        ob.H=x;
        ob.L=y;
    }
    else if(des=="B"){
        ob.B=x;
        ob.C=y;
    }
    else if(des=="D"){
        ob.D=x;
        ob.E=y;
    }
    //cout<<ob.H<<ob.L;

}

void LHLD(string v1,string v2,reg_state & ob)
{
    ob.H=v1;
    ob.L=v2;
}

string STA(reg_state &ob)
{
    return ob.A;
}

void ADD(string val, reg_state & ob,int ch)
{
    stringstream ss;
    int valR,valA;
    switch(ch){
    case 1:
        ss << hex << val;
        break;
    case 2:
        ss << hex << ob.reg_val(val);
        break;
    }
    stringstream sa,sb;
    sa << hex << ob.A;
    ss >> valR;
    sa >> valA;
    sb << hex <<(valA+valR);
    string tmp=sb.str();
    transform(tmp.begin(),tmp.end(),tmp.begin(), ::toupper);
    if(tmp.size()==1)
            tmp="0"+tmp;
    if((valA+valR)>0xFF){
        ob.CY=true;
        tmp=tmp.substr(1,2);
    }
    ob.A=tmp;
    return;
}

void ADI(string val, reg_state & ob)
{
    stringstream ss;
    int valA,valM;
    ss << hex << ob.A;
    ss >> valA;
    stringstream sa,sb;
    sa << hex << val;
    sa >> valM;
    sb << hex <<(valA+valM);
    string tmp=sb.str();
    transform(tmp.begin(),tmp.end(),tmp.begin(), ::toupper);
    if(tmp.size()==1)
            tmp="0"+tmp;

    if((valA+valM)>0xFF){
        ob.CY=true;
        tmp=tmp.substr(1,2);
    }
    ob.A=tmp;
}

void ADC(string val, reg_state & ob,int ch)
{
    stringstream ss;
    int valR,valA,valCY;
    switch(ch){
    case 1:
        ss << hex << val;
        break;
    case 2:
        ss << hex << ob.reg_val(val);
        break;
    }
    stringstream sa,sb,sc;
    sa << hex << ob.A;
    sc << hex << ob.CY;
    ss >> valR;
    sa >> valA;
    sc >> valCY;
    sb << hex <<(valA+valR+valCY);
    string tmp=sb.str();
    transform(tmp.begin(),tmp.end(),tmp.begin(), ::toupper);
    if(tmp.size()==1)
            tmp="0"+tmp;
     if(((valA+valCY)+valR)>0xFF){
        ob.CY=true;
        tmp=tmp.substr(1,2);
    }
    ob.A=tmp;
    return;
}

void SUB(string val,reg_state & ob,int ch)
{
    stringstream ss;
    int valR,valA;
    switch(ch){
    case 1:
        ss << hex << val;
        break;
    case 2:
        ss << hex << ob.reg_val(val);
        break;
    }
    stringstream sa,sb;
    sa << hex << ob.A;
    ss >> valR;
    sa >> valA;
    sb << hex <<(valA-valR);
    string tmp=sb.str();
    transform(tmp.begin(),tmp.end(),tmp.begin(), ::toupper);
    if(tmp.size()==1)
            tmp="0"+tmp;
    if(valR>valA){
        ob.CY=true;
        tmp=tmp.substr(6,2);
    }
    ob.A=tmp;
    return;
}

void SBB(string val, reg_state & ob,int ch)
{
    stringstream ss;
    int valR,valA,valCY;
    switch(ch){
    case 1:
        ss << hex << val;
        break;
    case 2:
        ss << hex << ob.reg_val(val);
        break;
    }
    stringstream sa,sb,sc;
    sa << hex << ob.A;
    sc << hex << ob.CY;
    ss >> valR;
    sa >> valA;
    sc >> valCY;
    sb << hex <<(valA-(valR+valCY));
    string tmp=sb.str();
    transform(tmp.begin(),tmp.end(),tmp.begin(), ::toupper);
    if(tmp.size()==1)
            tmp="0"+tmp;
     if((valR+valCY)>valA){
        ob.CY=true;
        tmp=tmp.substr(6,2);
    }
    ob.A=tmp;
    return;
}

void SUI(string val,reg_state & ob)
{
    stringstream ss;
    int valA,valM;
    ss << hex << ob.A;
    ss >> valA;
    stringstream sa,sb;
    sa << hex << val;
    sa >> valM;
    sb << hex <<(valA-valM);
    string tmp=sb.str();
    transform(tmp.begin(),tmp.end(),tmp.begin(), ::toupper);
    if(tmp.size()==1)
            tmp="0"+tmp;
     if(valM>valA){
        ob.CY=true;
        tmp=tmp.substr(6,2);
    }
    ob.A=tmp;
}

string MOV(string des,string src,reg_state & ob,int ch)
{
    switch(ch){
    case 1:
        cout<<"  moving to memory  "<<ob.reg_val(src)<<endl;
        return ob.reg_val(src);
    case 2:
        cout<<"  moving from memory  "<<src<<endl;
        ob.reg_change_val(des,src);
        return src;
    case 3:
        ob.reg_change_val(des,ob.reg_val(src));
        return src;
    }
}

void MVI(string des,string src,reg_state & ob)
{
    ob.reg_change_val(des,src);
    return;
}

void INR(string val, reg_state & ob)
{
    stringstream ss;
    int valR;
    stringstream sa;
    ss << hex << ob.reg_val(val);
    ss >> valR;
    if(valR>0xFF)
        ob.CY==true;
    sa << hex <<(valR+1);
    string tmp=sa.str();
    transform(tmp.begin(),tmp.end(),tmp.begin(), ::toupper);
    if(tmp.size()==1)
            tmp="0"+tmp;
    ob.reg_change_val(val,tmp);
}

void DCR(string val, reg_state & ob)
{
    lastdec=val;
    //cout<<endl<<"last decr"<<lastdec;
    stringstream ss;
    int valR;
    stringstream sa;
    ss << hex << ob.reg_val(val);
    ss >> valR;
    if((valR-1)==0)
        ob.Z=true;
    sa << hex <<(valR-1);
    string tmp=sa.str();
    transform(tmp.begin(),tmp.end(),tmp.begin(), ::toupper);
    if(tmp.size()==1)
            tmp="0"+tmp;
    ob.reg_change_val(val,tmp);
}

void INX(string des,string val, reg_state & ob)
{
    int v;
    stringstream sa,sb;
    sb << hex << val;
    sb >> v;
    sa << hex <<(v+1);
    val=sa.str();
    transform(val.begin(),val.end(),val.begin(), ::toupper);
    cout<<endl<<"  now value of m  "<<val<<endl;
    string x=val.substr(0,2);
    string y=val.substr(2,2);
    transform(x.begin(),x.end(),x.begin(), ::toupper);
    transform(y.begin(),y.end(),y.begin(), ::toupper);
    if(des=="H"){
        ob.H=x;
        ob.L=y;
    }
    else if(des=="B"){
        ob.B=x;
        ob.C=y;
    }
    else if(des=="D"){
        ob.D=x;
        ob.E=y;
    }

}

void DCX(string des,string val, reg_state & ob)
{
    stringstream ss;
    int v;
    ss << hex << val;
    ss >> v;
    stringstream sa;
    sa << hex <<(v-1);
    val=sa.str();
    cout<<endl<<"  now value of m  "<<val<<endl;
    string x=val.substr(0,2);
    string y=val.substr(2,2);
    transform(x.begin(),x.end(),x.begin(), ::toupper);
    transform(y.begin(),y.end(),y.begin(), ::toupper);
    if(des=="H"){
        ob.H=x;
        ob.L=y;
    }
    else if(des=="B"){
        ob.B=x;
        ob.C=y;
    }
    else if(des=="D"){
        ob.D=x;
        ob.E=y;
    }
}

void CMP(string val, reg_state & ob, int ch)
{
    stringstream ss;
    ob.CY=false;
    ob.Z=false;
    int valR,valA;
    switch(ch){
    case 1:
        ss << hex << val;
        break;
    case 2:
        ss << hex << ob.reg_val(val);
        break;
    }
    stringstream sa,sb;
    sa << hex << ob.A;
    ss >> valR;
    sa >> valA;
    cout<<endl<<"  now comparing  "<<valA<<"  "<<valR<<endl;
    if(valA<valR)
        ob.CY=true;
    else if(valA>valR)
        ob.CY=ob.Z=false;
    else
        ob.Z=true;
}

int JZ(reg_state &ob)
{
    stringstream ss;
    int v;
    ss << hex << ob.reg_val(lastdec);
    ss >> v;
    if(v==0)
        return 1;
    else
        return 0;
}

int JNZ(reg_state &ob)
{
    stringstream ss;
    int v;
    ss << hex << ob.reg_val(lastdec);
    ss >> v;
    if(v==0)
        return 0 ;
    else
        return 1;
}
