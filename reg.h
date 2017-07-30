#include<iostream>
#include<string>
using namespace std;
class reg_state
{
    public:
        string A,B,C,D,E,H,L,SP,PC;
        bool S,Z,AC,P,CY;
        reg_state()
        {
            A=B=C=D=E=H=L=SP=PC="";
            S=Z=AC=P=CY=false;
        }
        void show_state()
        {
            cout<<"A-->"<<A<<endl;
            cout<<"B-->"<<B<<endl;
            cout<<"C-->"<<C<<endl;
            cout<<"D-->"<<D<<endl;
            cout<<"E-->"<<E<<endl;
            cout<<"H-->"<<H<<endl;
            cout<<"L-->"<<L<<endl;
            cout<<"SP-->"<<SP<<endl;
            cout<<"PC-->"<<PC<<endl;
            cout<<"S->"<<S<<endl;
            cout<<"Z-->"<<Z<<endl;
            cout<<"AC-->"<<AC<<endl;
            cout<<"P-->"<<P<<endl;
            cout<<"CY-->"<<CY<<endl;

        }
        string reg_val(string s)
        {
            if(s=="A")
                return A;
            else if(s=="B")
                return B;
            else if(s=="C")
                return C;
            else if(s=="D")
                return D;
            else if(s=="E")
                return E;
            else if(s=="H")
                return H;
            else if(s=="L")
                return L;
        }
        void reg_change_val(string d,string v)
        {
            if(d=="A")
                A=v;
            else if(d=="B")
                B=v;
            else if(d=="C")
                C=v;
            else if(d=="D")
                D=v;
            else if(d=="E")
                E=v;
            else if(d=="H")
                H=v;
            else if(d=="L")
                L=v;
        }
};
