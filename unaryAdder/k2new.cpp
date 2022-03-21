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

//choose vertices
int n, l, k;
vector<vector<int>> vec2d;
vector<int> v;
void print2(int a, int b){ cout << a << " " << b << " 0\n";}
void print3(int a, int b, int c){ cout << a << " " << b << " " << c << " 0\n";}
void print4(int a, int b, int c, int d){ cout << a << " " << b << " " << c << " " << d << " 0\n";}
void iff(int a, int b){
    print2(a, -b);
    print2(-a, b);
}
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

void lex(vi x, vi p, int &start){
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
    start += l;

}

void lexConditional(vi x, vi p, int &start, int k1){
    assert(x.size()==p.size());
    int l = x.size();
    cout << -x[0] << " " << p[0] << " 0\n";
    for(int i=0;i<l;i++){
        cout << -x[i] << " " << start+i << " 0\n";
        cout << p[i] << " " << start+i << " 0\n";
        cout << k1 << " ";
        for(int j=0;j<i;j++){
            cout << -1*(start+j) << " ";
        }
        cout << -x[i] << " " << p[i] << " 0\n";
    }
    start += l;

}
vi k1(vi a, int &start){
    vector<int> pre, cur;
    iff(start, a[0]);

    //the first array contains two elements: first variable 0, first variable 1
    pre.push_back(-1);
    pre.push_back(start++);

    //loop all the i from 1 to a.size()-1
    for(int i = 1; i< a.size(); i++){
        cur.clear();
        cur.push_back(-1);
        //variable for if there's no 1 up until index i
        print2(-pre[1], start);
        print2(-a[i], start);
        print3(-start, pre[1], a[i]);
        cur.push_back(start++);
        
        //loop all the possible 1 count: 1 to i-1
        for(int j=2;j<=i;j++){
            int b = a[i], c = pre[j], d = pre[j-1];
            print2(-c, start);
            print3(-b, -d, start);
            print3(b, c, -start);
            print3(d, c, -start);
            cur.push_back(start++);
        }
        //cur[i] iff pre[i-1] and a[i]
        print2(-start, pre[i]);
        print2(-start, a[i]);
        print3(start, -pre[i], -a[i]);
        
        cur.push_back(start++);
        pre = cur;
        assert(pre.size()==i+2);

    }
    pre.erase(pre.begin());
    return pre;
}


//returns a vector of (0, 1) counter concatenated with (1, 1) counter
vi k2(vi a, vi b, int &st){
    vi ans;
    vi cnt01, cnt11, counter01, counter11;

    //writes variables to indicate (0, 1) pairs
    FOR(i, 0, a.size()-1){
        //st <-> -a[i] and b[i]
        //cnf: (A ∨ ¬B ∨ St) ∧ (¬St ∨ ¬A) ∧ (¬St ∨ B)
        print3(a[i], -b[i], st); print2(-st, -a[i]);  print2(-st, b[i]);
        cnt01.pb(st++);
    }


    //writes variables to indicate (1, 1) pairs
    FOR(i, 0, a.size()-1){
        //st <-> a[i] and b[i]
        //cnf: (-A ∨ ¬B ∨ St) ∧ (¬St ∨ A) ∧ (¬St ∨ B)
        print3(-a[i], -b[i], st); print2(-st, a[i]);  print2(-st, b[i]);
        cnt11.pb(st++);
    }
    //pass (0, 1) vector into binary adder
    counter01 = k1(cnt01, st);
    assert(counter01.size()==n);
    //pass (1, 1) vector into binary adder
    counter11 = k1(cnt11, st);
    assert(counter11.size()==n);

    ans.insert(ans.end(), counter01.begin(), counter01.end());
    ans.insert(ans.end(), counter11.begin(), counter11.end());
    return ans;
}

int checkEqual(vi a, vi b, int &st){
    int l = a.size();
    vi va;
    for(int i=0;i<l;i++){
        //(¬A ∨ ¬B ∨ C) ∧ (A ∨ B ∨ C) ∧ (¬B ∨ A ∨ ¬C) ∧ (¬A ∨ B ∨ ¬C)
        print3(-a[i], -b[i], st); print3(a[i], b[i], st); print3(-b[i], a[i], -st); print3(-a[i], b[i], -st);
        va.push_back(st++);
    }
    for(auto e:va){
        cout << -e << " ";
    }
    cout << st << " 0\n";
    for(auto e:va) print2(-st, e);
    st++;
    //st is one larger than the actual equal variable
    return st-1;
}
void cardLeq(vi a, vi b, int k1){
    for(int i=0;i<a.size();i++){
        print3(-a[i], b[i], k1);
    }
}

void cardLeq(vi a, vi b){
    for(int i=0;i<a.size();i++){
        print2(-a[i], b[i]);
    }
}
int main(int argc, char* argv[]){
    cout << "ok\n";
    //n is length and k is the number of colors, l is the length limit
    string outname = "k2";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l = stoi(argv[3]);
    // n = 20; k = 5; l = 5; lex = 1;

    outname += "_" + to_string(n) + ".out";
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
        vector<int> v1, v2;
        for(int j=1;j<=n;j++){
            if(i==j || i+1==j) continue; 
            v1.push_back(flat(i, j));
            v2.push_back(flat(i+1, j));
        }
        lex(v1, v2,  idx);
    }
    //count number of 1s in each row
    // cout << "idx " << idx << "\n";
    

    vector<vi> row;
    vector<int> offset; row.push_back(offset);
    for(int i=1;i<=n;i++){
        vi a;
        for(int j=1;j<=n;j++){
            a.push_back(flat(i, j));
        }
        row.push_back(a);
    }

    /*
        encode k=1 for first row
    */
    vi topk1 = k1(row[1], idx);

    /*
        encode k=2 additional constraints for first two rows
    */
    vi topk2 = k2(row[1], row[2], idx); 


    for(int i=1;i<=n;i++){
        /*
            encode k=1 for row i of adj matrix
        */

        //curk1 is the unary adder that stores the k=1 constraint of the current row. 
        vi curk1 = k1(row[i], idx);
        // lex(topk1, curk1, idx);
        cardLeq(topk1, curk1);
        int p1 = checkEqual(topk1, curk1, idx);


        for(int j=1; j<=n;j++){
            if(i==j) continue;
            if(i==1&&j==2) continue;

            /*
                encode k=2 for row i , j
            */
            vi curk2 = k2(row[i], row[j],  idx);

            /*
                compares the k=2 encoding of first two rows and current pair of rows. 
            */
           int p2 = idx++;
           //(Idx1 ∨ P2) ∧ (¬Flat ∨ P2) ∧ (¬P2 ∨ -Idx1 ∨ Flat)
           print2(p1, p2); print2(-flat(i, j), p2); print3(-p2, -p1, flat(i, j));
           cardLeq(topk2, curk2, p2);
        }
    }
    cout << endl;
    return 0;

}