#include<iostream>
#include"miller_rabin.cpp"
#include<fstream>
#include<string>
using namespace std;

int gcdExtended(int a, int b, int* x, int* y);
int modInverse(int A, int M)
{
    int x, y;
    int g = gcdExtended(A, M, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist";
    else {
        int res = (x % M + M) % M;
        return res;
    }
}
 
// Function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int* x, int* y)
{
 
    // Base Case
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    // To store results of recursive call
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}
 
class RSA{
  long long int p,q,n,phi_n,a,inv_a;
  public:
  RSA(int x,int y){
    p=gen_prime(x);
    q=gen_prime(y);
    set_n();
    a=coprime(phi_n/11);
    set_a_inv();
  }
  int coprime(int a){
       while (true){
           if (miller_rabin(a,10)){
               if (phi_n%a !=0){
                return a;
               }
           }
           a++;
       }
  }
  void set_n(){  n=p*q; phi_n=(p-1)*(q-1);}
  int give_encrpt(unsigned long long int x){
     return power(x,a,n);
  }
  void set_a_inv(){
     inv_a = modInverse(a,phi_n);
  }
  unsigned long long int decrypt( int x){
        long long int c= power(x,inv_a,n);
        return c;
  }
  int getn() {return n;}
  int geta() {return a;}

  void decrypt_file(string filename){
    fstream file;
    ofstream out; 
    out.open("output2.txt");
   string word;
   file.open(filename.c_str());
   while(file >> word) { //take word and print
      long long int ans = decrypt(stoi(word));
      string  s="";
       while (ans>0){
          s = char('a'-11+ans%100)+s;
          ans = ans/100;
      }
      out << s<<" ";
   }
   file.close();
  }

  void read_word_by_word(string filename) {
   fstream file;
   ofstream out; 
   out.open("output.txt");
   string word;
   file.open(filename.c_str());
   while(file >> word) { //take word and print
       long long  n=0;
      for (int i=0;i<word.length();i++){
          n = int(word[i]-'a'+11)+n*100;
      }
      out << give_encrpt(n)<<" ";
   }
   file.close();
}
};

int main(){
    RSA a(70987,3789);
    a.read_word_by_word("file1.txt");
    a.decrypt_file("output.txt");
}

