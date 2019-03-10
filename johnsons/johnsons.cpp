/*
Program rozwi¹zuj¹cy problem przep³ywowy algorytmem Johnsonsa, wariant 2 oraz 3 maszynowy
Dane wpisujemy zgodnie z instancj¹ ta000

*/

#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <fstream>
#include <vector>
using namespace std;

class zadanie
{
    public:
  int index;
  int M1;
  int M2;
  int M3;
  zadanie() {
		index = 0;
		M1 = 0;
		M2 = 0;
		M3 = 0;
	}
	zadanie(int t, int e,int p, int g) {
		index = t;
		M1 = e;
		M2 = p;
		M3 = g;
}
};

/*
Funkcja wpisuj¹ca do tablicy kolejnosc zadan, zgodnie z algorytmem Johnsonsa
oraz zwracaj¹ca bie¿¹ce zadanie do usuniecia
*/
int minimum(vector<zadanie>P,int n, vector<int>&kolejnosc, int& y, int& z)
{
    int tab1[n], tab2[n];
    for(int i =0;i<n;i++)
    {
        tab1[i] = P[i].M1;
        tab2[i] = P[i].M2;
    }
    int small1 = tab1[0];
    int small2 = tab2[0];
      int   m1 = 0;
    int     m2 = 0;
        
        for(int i = 0; i < n; i++){
         if(tab1[i] < small1){
                small1 = tab1[i];
                m1 = i;
         }
          if(tab2[i] < small2){
                small2 = tab2[i];
                m2 = i;
         }
        }
        
    if(P[m1].M1<P[m2].M2)
    {
    kolejnosc.insert(kolejnosc.begin()+z,P[m1].index);
    z++;
   // cout<<P[m1].index <<"   "<<"z = "<<z<<endl;
    return m1;
    }
    else if(P[m1].M1==P[m2].M2)
    {
        if(m1<=m2){
    kolejnosc.insert(kolejnosc.begin()+z,P[min(m1,m2)].index);
    z++;
   // cout<<P[min(m1,m2)].index <<"   "<<"z = "<<z<<endl;
        }
        else
        {
          kolejnosc.insert(kolejnosc.begin()+kolejnosc.size()-y,P[min(m1,m2)].index);
    y++;
   // cout<<P[min(m1,m2)].index <<"   "<<"y = "<<y<<endl;
        }
    return min(m1,m2);
    }
    else
    {
    kolejnosc.insert(kolejnosc.begin()+kolejnosc.size()-y,P[m2].index);
    y++;
    //cout<<P[m2].index <<"   "<<"y = "<<y<<endl;
    return m2;
    }
}

/*
funkcja do wyliczania cmax
*/
int getcmacx(vector<zadanie> P, int n, vector<int>myints,int m)
{
    int cmax = 0;
    int D1 = 0;
    int D2 = 0;
    for(int i=0;i<n;i++)
    {
        D1=D1+P[myints[i]-1].M1;
        if(D2<D1)
        D2 = D1+P[myints[i]-1].M2;
        else
        D2 = D2+P[myints[i]-1].M2;
        if(cmax<D2)
        cmax = D2+P[myints[i]-1].M3;
        else
        cmax = cmax+P[myints[i]-1].M3;
    }
    if(m>2)
    return cmax;
    else
    return D2;
}
/*
funkcja usuwaj¹ca z zadanie z tablicy
*/
void gettab(vector<zadanie>& tab, int m)
{
    tab.erase(tab.begin()+m);
}
/*
funkcja tworz¹ca z 3 maszyn dwie maszyny wirtualne
*/
void trzy_do_dwa(vector<zadanie>&P, int n)
{
    for(int i = 0;i<n;i++)
    {
        P[i].M1 = P[i].M1 + P[i].M2;
        P[i].M2 = P[i].M2 + P[i].M3;
        P[i].index = i+1;
        P[i].M3 = 0;
    }
    cout<<"Powsta³y maszyny wirtualne : "<<endl;
    for(int i = 0;i<n;i++)
    {
        cout<<P[i].M1<<" "<<P[i].M2<<endl;
    }
}
int main () {
    int n, n_m, m,y=0,z=0,cmax1=0;
    zadanie K;
    ifstream data("data.txt");
    data>>n>>n_m;
    vector<zadanie> P;
    vector<int> kolejnosc;
    if(n_m==3){
   for(int i=0;i<n;i++)
    {
        K.index = i+1;
        data>>K.M1>>K.M2>>K.M3;
        P.push_back(K);
    }
    }
    else
    for(int i=0;i<n;i++)
    {
        K.index = i+1;
        data>>K.M1>>K.M2;
        P.push_back(K);
    }
    vector<zadanie>kopia = P;
    if(n_m>2)
    trzy_do_dwa(P,n);
    while(P.size()>=1)
    {
        m = minimum(P,P.size(),kolejnosc,y,z);
        gettab(P,m);
    }

    cout<<"Uzyskana kolejnosc : "<<endl;
    for(int i =0;i<n;i++)
    {
        cout<<kolejnosc[i]<<' ';
    }
    
        cmax1 = getcmacx(kopia,n,kolejnosc,n_m);
    cout<<endl<<"cmax = "<<cmax1;
return 0;
}