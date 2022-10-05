#include<iostream>
#include<set>
#include<iterator>
#include<map>
using namespace std;

class Relation{
multimap<int, int> myrelation;
multimap<int, int> inverse;
map<int ,int>function;
map<int ,int>inv_function;
set<int> domain;
set<int> range;
public:
 
void insert(int a ,int b){
    if (domain.count(a)==0){domain.insert(a);}
    if (range.count(b)==0){range.insert(b);}
    inverse.insert(pair<int, int>(b, a));
    myrelation.insert(pair<int, int>(a, b));
}

set<int> value(int a){
set<int>match;
multimap<int, int>::iterator itr;
for ( itr = myrelation.begin(); itr != myrelation.end(); ++itr) {
    if(itr->first == a){
        match.insert(itr->second);
    }
}
    return match;
}

set<int> rel_inv(int a){
set<int>match;
multimap<int, int>::iterator itr;
for ( itr = myrelation.begin(); itr != myrelation.end(); ++itr) {
    if(itr->second == a){
        match.insert(itr->second);
    }
}
    return match;
}
int func_value(int a){
   return function[a];
}

void setfunction(){
   set<int> mapped_value;
   set<int>::iterator itr;
   for (itr= domain.begin();itr!=domain.end();++itr)
    {
          set<int>possible= value(*itr);
          int value=-1;
          set<int>::iterator count;
          for (count= possible.begin();count!=possible.end();++count)
          {  int key=*count;
             if (mapped_value.find(key) == mapped_value.end()){
                 value=*count;
                 mapped_value.insert(value);
                 break;
             }
          }
          if(value==-1){
            value=shift(*itr,mapped_value);
            mapped_value.insert(value);
          }
           inv_function[value]=*itr;
            function[*itr]=value;
     
    }
}
int shift(int a,set<int>bvalues){

set<int>possible= value(a);
set<int>inv_poss;
set<int>::iterator count;
 for (count= possible.begin();count!=possible.end();++count){
      inv_poss.insert(inv_function[*count]);
 }
set<int>next_b;
for (count= inv_poss.begin();count!=inv_poss.end();++count){
    set<int> val_inv_poss= value(*count);
    set<int>::iterator vary;
    std::set<int> result;
    std::set_difference(val_inv_poss.begin(), val_inv_poss.end(), bvalues.begin(), bvalues.end(),
    std::inserter(result, result.end()));
    if (result.size() !=0){
          int y=function[*count];
          function[*count]=*result.begin();
          inv_function[*result.begin()]=*count;
          return y;
    }
}

for (count= inv_poss.begin();count!=inv_poss.end();++count){
set<int> val_inv_poss= value(*count);
set_union(bvalues.begin(), bvalues.end(),val_inv_poss.begin(), val_inv_poss.end(), inserter(bvalues, bvalues.begin()));
}

for (count= inv_poss.begin();count!=inv_poss.end();++count){
    int x = shift(*count,bvalues);
    if(x==-1){continue;}
    else{  cout << x<<endl;
           int y=function[*count];
           function[*count]=x;
           inv_function[x]=*count;
           return y;
    }
}
return -1;
}
};

int main(){
    Relation a;
    while(true){
    cout << "\nENTER\n1.ENTER RELATION\n2.FUNCTIONAL VALUE\n3.EXIT\n";
    int x;
    cin >> x;
    if (x==1){
        cout <<"\nENTER A AND B WHERE A R B";
        int A,B;
        cout << "\nvalue of A ";
        cin >>A;
        cout << "\nvalue of B ";
        cin >>B;
        a.insert(A,B);
        cout << "\nsuccessfully inserted"<<endl;
    }
    if (x==2){
        a.setfunction();
        cout << "\nENTER NO WHOSE FUNCTIONAL VALUE YOU WANT\n";
        int x;
        cin >>x;
        cout<<"\nF("<<x<<") is "<<a.func_value(x)<<endl;

    }
    if (x==3){
        return 0;
    }
    }
}