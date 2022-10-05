#include<iostream>
#include<ctime>
using namespace std;
long long unsigned int  power(long long unsigned int  a, long long unsigned int  r, long long unsigned int  n){
    long long unsigned int  ans=1;
    long long unsigned int  exponential = a%n;
while (r>0)
{  if (r%2==1)
   {ans = (ans*exponential)%n;}
   exponential= (exponential*exponential)%n;
   r = r/2;
}
return ans;
}

bool coprime(long long unsigned int  n , long long unsigned int  m){
if(n==0){
    return 0;
}
if (n == 1){
    return 1;
}
else{
    return coprime(m%n,n);
}
}
bool isprime(long long unsigned int  n, long long unsigned int  a){
    long long unsigned int  x = n-1;
    if(!coprime(a,n)){
        return false;
    }
    else{
        if(power(a,n-1,n)!=1){
            return false;
        }
        else{
            while(x%2 == 0){
                if(power(a,x/2,n)!=1 && power(a,x/2,n)!=n-1){
                    return false;
                }
                else if (power(a,x/2,n) == 1){
                    x = x/2;
                    continue;
                }
                else{
                    break;
                }
            }
        }
    }
    return true;
}

bool miller_rabin(long long unsigned int n, int x){ // X is number of times the random number is generated. 
    bool answer = true;
    while(x>0){
        long long unsigned int  a = 2+rand()%(n-2);
        if(!isprime(n,a)){
            answer = false;
            break;
        }
        x--;
    }
    return answer;
}
int gen_prime(int x){
    for(int i =x ;i<100000000;i=i+1){
        if(miller_rabin(i,10)){
            return i;
        }
}
}
/*int  main(){
    // long long unsigned int  n;
    // cin>>n;
    srand(time(0));
    int count = 0;
    for(int i =3 ;i<100000000;i=i+2){
        // long long unsigned int  a = 2+rand()%(i-2);
        if(miller_rabin(i,5)){
            count++;
            cout<<i<<endl;
        }
    }
    cout<<(count+1)<<endl;
}*/