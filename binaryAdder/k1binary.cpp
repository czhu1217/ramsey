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

/*
    Input: takes in two digits a, b and st, a starting index to write auxillary variables
    Output: returns {s, c} : {resulting current digit in the sum, carry}
*/
pi halfAdder(int a, int b, int st){
    int s = st;
    //s <-> a xor b
    //s <-> (-a and b) or (a and -b)
    /*cnf form: 
        (A ??? ??B ??? S) ??? (??A ??? B ??? S) ??? (??B ??? ??A ??? ??S) ??? (A ??? B ??? ??S)
    */

    print3(a, -b, s);
    print3(-a, b, s);
    print3(-b, -a, -s);
    print3(a, b, -s);
    st++;

    int c = st;
    //c <-> a and b
    print3(-a, -b, c);
    print2(-c, a);
    print2(-c, b);

    return {s, c};

}
/*
    Input: 
        a, b: 2 binary digits
        c: carry from previous calculation
        st: starting index to write auxillary variables
    Output: returns {s, co} : {resulting current digit in the sum, carry}
*/
pi fullAdder(int a, int b, int c, int st){
    int s = st;
    //st (s) <-> a xor b xor c
    /*cnf form:
        (B ??? A ??? ??C ??? St) ??? (??C ??? A ??? B ??? St) ??? (B ??? ??C ??? A ??? St) ??? (??C ??? ??A ??? ??B ??? St)
        ??? (B ??? C ??? ??A ??? St) ??? (B ??? ??A ??? C ??? St) ??? (A ??? C ??? ??B ??? St) ??? (??St ??? ??A ??? C ??? ??B)
        ??? (??St ??? ??B ??? C ??? ??A) ??? (??St ??? ??B ??? A ??? ??C) ??? (??St ??? ??A ??? B ??? ??C) ??? (??St ??? C ??? A ??? B)
    */
    print4(b, a, -c, st); print4(-c, a, b, st); print4(b, -c, a, st); print4(-c, -a, -b, st);
    print4(b, c, -a, st); print4(b, -a, c, st); print4(a, c, -b, st); print4(-st, -a, c, -b);
    print4(-st, -b, c, -a); print4(-st, -b, a, -c); print4(-st, -a, b, -c); print4(-st, c, a, b);
    st++;
    int co = st;
    //st (co) <-> (a or b) and (a or c) and (b or c)
    //(??A ??? ??B ??? St) ??? (??C ??? ??A ??? ??B ??? St) ??? (??C ??? ??B ??? St) ??? (??A ??? ??C ??? St)
    //(??A ??? ??B ??? ??C ??? St) ??? (??St ??? A ??? B) ??? (??St ??? A ??? C) ??? (??St ??? B ??? C)
    print3(-a, -b, st); print4(-c, -a, -b, st); print3(-c, -b, st); print3(-a, -c, st);
    print4(-a, -b, -c, st); print3(-st, a, b); print3(-st, a, c); print3(-st, b, c);
    return {s, co};
}

//input: Two non-negative i-bit numbers a and b (stored as vectors of the same length), least significant bit first
//output:  an n i + 1-bit non-negative number (stored in a vector) which is the sum of a and b, least significant bit first.
vi rippleAdder(vi a, vi b, int &st){
    assert(a.size()==b.size());
    int l = a.size();
    vi ans;

    //compute the least sig bit
    pi p = halfAdder(a[0], b[0], st);
    st += 2;
    //store least sig bit into answer vector 
    ans.pb(p.f);

    //computer the 2nd to second last digit
    FOR(i, 1, l-1){
        //compute current (digit, carry) pair
        p = fullAdder(a[i], b[i], p.s, st);
        st += 2;
        //store current digit into answer
        ans.pb(p.f);
    }
    //store last carry into answer
    ans.pb(p.s);
    return ans;
}

//zero is a variable that's always set to false, one is a variable that's always set to true
int zero, one;
vi k1(vector<int> a, int &start){
    //ans will be used as the accumulated sum
    vi ans;
    //initially ans is 0
    ans.pb(zero); 

    //compute the sum by adding each digit with the accumulated sum
    FOR(i, 0, a.size()-1){
        vi cur;
        //len is the maximum possible length of ans up to this point
        int len = log2(i+1)+1;

        //make cur the same length as ans by adding a[i] to the front and leading zeros afterwards
        cur.pb(a[i]); 
        while(cur.size()<len) cur.pb(zero);

        //prune ans if it's longer than len (getting rid of most sig digit since we know it must be 0)
        while(ans.size()>len){
            int z = ans.back();
            ans.pop_back();
        }

        //compute new accumulated sum by passing in current sum, digit, starting index of new var to rippleAdder
        ans = rippleAdder(ans, cur, start);
    }

    return ans;
}
int main(int argc, char* argv[]){
    string outname = "k2_";
    string tmp;
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l = stoi(argv[3]);


    outname += to_string(n) + ".out";
    freopen(outname.c_str(), "w", stdout);

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

    // cout << "huh";
    

    vector<vi> row;
    vi offset; row.pb(offset);
    for(int i=1;i<=n;i++){
        vi a;
        for(int j=1;j<=n;j++){
            a.push_back(flat(i, j));
        }
        row.push_back(a);
    }
    //set two variables to be used as 1 and 0 in the binary adder
    zero = idx, one = idx+1;
    cout << -idx << " 0\n"; idx++;
    cout << idx << " 0\n"; idx++;

    //computer binary counter of top row
    vi topk1 = k1(row[1], idx);
    //reverse the counter to be most significant digit first
    reverse(topk1.begin(), topk1.end());

    for(int i=2;i<=n;i++){
        vi curk1;
        //computer binary counter of current row
        curk1 = k1(row[i], idx);
        //reverse the counter to be most significant digit first
        reverse(curk1.begin(), curk1.end());
        //compare the binary counters to make sure the counter for first row is lexicographically smaller than the current row counter
        lex2(topk1, curk1, idx);
        idx += topk1.size();
    }
    cout << endl;
    return 0;

}