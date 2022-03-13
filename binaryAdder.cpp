#include <bits/stdc++.h>
using namespace std; 
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<ll> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
 
#define FOR(i, a, b) for (ll i=a; i<=(b); i++)
#define F0R(i, a) for (ll i=0; i<(a); i++)
#define FORd(i,a,b) for (ll i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (ll i = (a)-1; i >= 0; i--)
 
#define sz(x) (ll)(x).size()
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert
void print2(int a, int b){ cout << a << " " << b << " 0\n";}
void print3(int a, int b, int c){ cout << a << " " << b << " " << c << " 0\n";}
void print4(int a, int b, int c, int d){ cout << a << " " << b << " " << c << " " << d << " 0\n";}
void iff(int a, int b){
    print2(a, -b);
    print2(-a, b);
}
pi halfAdder(int a, int b, int st){
    print3(a, -b, st);
    print3(-a, b, st);
    print3(-b, -a, -st);
    print3(a, b, -st);
    int s = st;
    st++;
    int c = st;
    print3(-a, -b, st);
    print2(-st, a);
    print2(-st, b);
    return {s, c};

}
pi fullAdder(int a, int b, int c, int st){
    //(¬A ∨ C ∨ ¬B) ∧ (¬B ∨ C ∨ ¬A) ∧ (¬B ∨ A ∨ ¬C) ∧ (¬A ∨ B ∨ ¬C) ∧ (C ∨ A ∨ B) ∧ (C ∨ B ∨ A)
    
    
}
vi binaryAdd(vi a, vi b, int st){
    vi ans;
    pi p0 = halfAdder(a[0], b[0], st);
    st += 2;

    

}

int main(){
 

    return 0;
}