#include <algorithm>
#include <cassert>
#include <bitset>
#include <iterator>
#include <math.h>
#include <new>
#include <numeric>
#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <array>
#include <stdexcept>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <sstream>
using namespace std; 
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<int> vi;
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
int n ,k, l; vi v;
int flat(int i, int j){ return (i-1)*n+j; }

void addEdges(int sign){
    int a, b;
    vector<int> tmp;
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            // if(i==j) continue;
            a = v[i]; b = v[j];
            #ifdef DEBUG
            #else
            cout << sign*flat(a, b)<< " ";
            #endif
            // cout << sign*((b-1)*n+a) << " ";
        }
    }
    #ifdef DEBUG
    #else
    cout << " 0\n";
    #endif
}

void addEdges2(int sign){
    int a, b;
    vector<int> tmp;
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            // if(i==j) continue;
            a = v[i]; b = v[j];
            // cout << sign*flat(a, b)<< " ";
            // cout << sign*((b-1)*n+a) << " ";
            tmp.push_back(sign*flat(a, b));
        }
    }
    #ifdef DEBUG
    #else
    for(int i=0;i<tmp.size();i++){
        for(int j=0;j<tmp.size();j++){
            if(j==i) continue;
            cout << tmp[j] << " ";
        }
        cout << "0\n";
    }
    #endif
}

void pickV(int cur,int m, int sign){
    if(v.size()==m){
        addEdges2(sign);
        return;
    }
    if(cur>n) return;
    v.push_back(cur);
    pickV(cur+1, m, sign);
    v.pop_back();
    pickV(cur+1, m, sign);
}

void lex2(vi x, vi p, int start){
    assert(x.size()==p.size());
    int l = x.size();
    cout << -x[0] << " " << p[0] << " 0\n";
    for(int i=0;i<l;i++){
        cout << -x[i] << " " << start+i << " 0\n";
        cout << p[i] << " " << start+i << " 0\n";
        for(int j=0;j<i;j++){
            cout << -1*(start+j) << " ";
        }
        cout << -x[i] << " " << p[i] << " 0\n";
    }

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
    //(B ∨ A ∨ ¬C ∨ St) ∧ (¬C ∨ A ∨ B ∨ St) ∧ (B ∨ ¬C ∨ A ∨ St) ∧ (¬C ∨ ¬A ∨ ¬B ∨ St)
    // ∧ (B ∨ C ∨ ¬A ∨ St) ∧ (B ∨ ¬A ∨ C ∨ St) ∧ (A ∨ C ∨ ¬B ∨ St) ∧ (¬St ∨ ¬A ∨ C ∨ ¬B)
    // ∧ (¬St ∨ ¬B ∨ C ∨ ¬A) ∧ (¬St ∨ ¬B ∨ A ∨ ¬C) ∧ (¬St ∨ ¬A ∨ B ∨ ¬C) ∧ (¬St ∨ C ∨ A ∨ B)
    print4(b, a, -c, st); print4(-c, a, b, st); print4(b, -c, a, st); print4(-c, -a, -b, st);
    print4(b, c, -a, st); print4(b, -a, c, st); print4(a, c, -b, st); print4(-st, -a, c, -b);
    print4(-st, -b, c, -a); print4(-st, -b, a, -c); print4(-st, -a, b, -c); print4(-st, c, a, b);
    int s = st;
    st++;
    int co = st;
    //(¬A ∨ ¬B ∨ St) ∧ (¬C ∨ ¬A ∨ ¬B ∨ St) ∧ (¬C ∨ ¬B ∨ St) ∧ (¬A ∨ ¬C ∨ St)
    //(¬A ∨ ¬B ∨ ¬C ∨ St) ∧ (¬St ∨ A ∨ B) ∧ (¬St ∨ A ∨ C) ∧ (¬St ∨ B ∨ C)
    print3(-a, -b, st); print4(-c, -a, -b, st); print3(-c, -b, st); print3(-a, -c, st);
    print4(-a, -b, -c, st); print3(-st, a, b); print3(-st, a, c); print3(-st, b, c);
    return {s, co};
}
//requires: Two non-negative i-bit numbers a and b, least significant bit first
//ensures: An i + 1-bit non-negative number which is the sum of a and b, least significant bit first.
vi rippleAdder(vi a, vi b, int &st){
    assert(a.size()==b.size());
    int l = a.size();
    vi ans;
    pi p0 = halfAdder(a[0], b[0], st);
    st += 2;
    ans.pb(p0.f);
    FOR(i, 1, l-1){
        p0 = fullAdder(a[i], b[i], p0.s, st);
        st += 2;
        ans.pb(p0.f);
    }
    ans.pb(p0.s);
    return ans;
}
int zero, one;
vi k1(vector<int> a, int &start){
    vi ans;
    ans.pb(zero); 
    FOR(i, 0, a.size()-1){
        vi tmp;
        int len = log2(i+1)+1;
        int dif1 = max((int)(len-ans.size()),0);
        tmp.pb(a[i]); while(tmp.size()<len) tmp.pb(zero);
        while(ans.size()>len){
            int z = ans.back();
            ans.pop_back();
        }
        ans = rippleAdder(ans, tmp, start);
    }
    return ans;
}
int main(int argc, char* argv[]){
    cout << "ok\n";
    //n is length and k is the number of colors, l is the length limit
    string outname = "binadd";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    bool lex;
    cin >> n >> k >> l;
    // n = 20; k = 5; l = 5; lex = 1;

    outname += to_string(n) + "_" + to_string(k) + + "_" + to_string(l) + ".out";
    #ifdef DEBUG
        printf("debug\n");
    #else 
        freopen(outname.c_str(), "w", stdout);
    #endif

    pickV(1, k, 1);
    pickV(1, l, -1);
    //ensures symmetry
    for(int i=1;i<=n;i++){
        cout << -flat(i, i) << " 0\n";
        for(int j=1;j<=n;j++){
            cout << flat(i, j) << " " << -flat(j, i) << " 0\n";
            cout << -flat(i, j) << " " << flat(j, i) << " 0\n";
        }
    }

    int idx = n*n+1;

    for(int i=1;i<n;i++){
        vi v1, v2;
        for(int j=1;j<=n;j++){
            if(i==j || i+1==j) continue; 
            v1.push_back(flat(i, j));
            v2.push_back(flat(i+1, j));
        }
        lex2(v1, v2,  idx);
        idx += v1.size();
    }
    //count number of 1s in each row
    // cout << "idx " << idx << "\n";
    

    vector<vi> row;
    vi offset; row.pb(offset);
    for(int i=1;i<=n;i++){
        vi a;
        for(int j=1;j<=n;j++){
            a.push_back(flat(i, j));
        }
        row.push_back(a);
    }
    zero = idx, one = idx+1;
    cout << -idx << " 0\n"; idx++;
    cout << idx << " 0\n"; idx++;

    vi topk1 = k1(row[1], idx);
    reverse(topk1.begin(), topk1.end());

    for(int i=2;i<=n;i++){
        vi curk1;
        curk1 = k1(row[i], idx);
        reverse(curk1.begin(), curk1.end());
        lex2(topk1, curk1, idx);
        idx += topk1.size();
    }
    cout << endl;
    return 0;

}