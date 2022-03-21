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
#include <cassert>
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
/*
    Input: takes in two digits a, b and st, a starting index to write auxillary variables
    Output: returns {s, c} : {resulting current digit in the sum, carry}
*/
pi halfAdder(int a, int b, int st){
    int s = st;
    //s <-> a xor b
    //s <-> (-a and b) or (a and -b)
    /*cnf form: 
        (A ∨ ¬B ∨ S) ∧ (¬A ∨ B ∨ S) ∧ (¬B ∨ ¬A ∨ ¬S) ∧ (A ∨ B ∨ ¬S)
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
        (B ∨ A ∨ ¬C ∨ St) ∧ (¬C ∨ A ∨ B ∨ St) ∧ (B ∨ ¬C ∨ A ∨ St) ∧ (¬C ∨ ¬A ∨ ¬B ∨ St)
        ∧ (B ∨ C ∨ ¬A ∨ St) ∧ (B ∨ ¬A ∨ C ∨ St) ∧ (A ∨ C ∨ ¬B ∨ St) ∧ (¬St ∨ ¬A ∨ C ∨ ¬B)
        ∧ (¬St ∨ ¬B ∨ C ∨ ¬A) ∧ (¬St ∨ ¬B ∨ A ∨ ¬C) ∧ (¬St ∨ ¬A ∨ B ∨ ¬C) ∧ (¬St ∨ C ∨ A ∨ B)
    */
    print4(b, a, -c, st); print4(-c, a, b, st); print4(b, -c, a, st); print4(-c, -a, -b, st);
    print4(b, c, -a, st); print4(b, -a, c, st); print4(a, c, -b, st); print4(-st, -a, c, -b);
    print4(-st, -b, c, -a); print4(-st, -b, a, -c); print4(-st, -a, b, -c); print4(-st, c, a, b);
    st++;
    int co = st;
    //st (co) <-> (a or b) and (a or c) and (b or c)
    //(¬A ∨ ¬B ∨ St) ∧ (¬C ∨ ¬A ∨ ¬B ∨ St) ∧ (¬C ∨ ¬B ∨ St) ∧ (¬A ∨ ¬C ∨ St)
    //(¬A ∨ ¬B ∨ ¬C ∨ St) ∧ (¬St ∨ A ∨ B) ∧ (¬St ∨ A ∨ C) ∧ (¬St ∨ B ∨ C)
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
    reverse(ans.begin(), ans.end());
    return ans;
}

//returns a vector of 3 numbers: first for start of count of (1, 1) pairs, second for (0, 1) pairs, third for new start
vi k2(vi a, vi b, int &st){
    vi ans;
    int l = a.size();
    vi cnt01, cnt11, bicounter01, bicounter11;

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
    bicounter01 = k1(cnt01, st);
    //pass (1, 1) vector into binary adder
    bicounter11 = k1(cnt11, st);
    ans.insert(ans.end(), bicounter01.begin(), bicounter01.end());
    ans.insert(ans.end(), bicounter11.begin(), bicounter11.end());
    return ans;
}

vi k3(vi a, vi b, vi c, int &st){
    vi ans;
    vi cnt001, cnt011, cnt101, cnt111, counter001, counter011, counter101, counter111;
    FOR(i, 0, a.size()-1){
        //st <-> -a[i] and -b[i] and c[i]
        //(A ∨ B ∨ ¬C ∨ St) ∧ (¬St ∨ ¬A) ∧ (¬St ∨ ¬B) ∧ (¬St ∨ C)
        print4(a[i], b[i], -c[i], st); print2(-st, -a[i]); print2(-st, -b[i]); print2(-st, c[i]);
        cnt001.pb(st++);
    }
    FOR(i, 0, a.size()-1){
        //st <-> -a[i] and b[i] and c[i]
        //(A ∨ B ∨ ¬C ∨ St) ∧ (¬St ∨ ¬A) ∧ (¬St ∨ ¬B) ∧ (¬St ∨ C)
        print4(a[i], -b[i], -c[i], st); print2(-st, -a[i]); print2(-st, b[i]); print2(-st, c[i]);
        cnt011.pb(st++);
    }
    FOR(i, 0, a.size()-1){
        //st <-> a[i] and -b[i] and c[i]
        //(A ∨ B ∨ ¬C ∨ St) ∧ (¬St ∨ ¬A) ∧ (¬St ∨ ¬B) ∧ (¬St ∨ C)
        print4(-a[i], b[i], -c[i], st); print2(-st, a[i]); print2(-st, -b[i]); print2(-st, c[i]);
        cnt101.pb(st++);
    }
    FOR(i, 0, a.size()-1){
        //st <-> a[i] and b[i] and c[i]
        //(A ∨ B ∨ ¬C ∨ St) ∧ (¬St ∨ ¬A) ∧ (¬St ∨ ¬B) ∧ (¬St ∨ C)
        print4(-a[i], -b[i], -c[i], st); print2(-st, a[i]); print2(-st, b[i]); print2(-st, c[i]);
        cnt111.pb(st++);
    }
    counter001 = k1(cnt001, st);
    counter011 = k1(cnt011, st);
    counter101 = k1(cnt101, st);
    counter111 = k1(cnt111, st);

    ans.insert(ans.end(), counter001.begin(), counter001.end());
    ans.insert(ans.end(), counter011.begin(), counter011.end());
    ans.insert(ans.end(), counter101.begin(), counter101.end());
    ans.insert(ans.end(), counter111.begin(), counter111.end());
    return ans;
}


int main(int argc, char* argv[]){
    cout << "ok\n";
    //n is length and k is the number of colors, l is the length limit
    string outname = "k3_";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l = stoi(argv[3]);
    // n = 20; k = 5; l = 5; lex = 1;

    outname += to_string(n)  + ".out";
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
        idx += v1.size();
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

    //set two variables to be used as 1 and 0 in the binary adder
    zero = idx, one = idx+1;
    cout << -idx << " 0\n"; idx++;
    cout << idx << " 0\n"; idx++;
    /*
        encode k=1 for first row
    */
    vi topk1 = k1(row[1], idx);
    // reverse(topk1.begin(), topk1.end());

    /*
        encode k=2 additional constraints for first two rows
    */
    vi k2additional = k2(row[1], row[2], idx); 
    // // // assert(k2additional.size()==2*n);
    vi topk2;
    topk2.insert(topk2.end(), topk1.begin(), topk1.end());
    topk2.insert(topk2.end(), k2additional.begin(), k2additional.end());
    // assert(topk2.size()==3*n);

    vi k3additional = k3(row[1], row[2], row[3], idx);
    vi topk3;
    topk3.insert(topk3.end(), topk2.begin(), topk2.end());
    topk3.insert(topk3.end(), k3additional.begin(), k3additional.end());



    for(int i=1;i<=n;i++){
        /*
            encode k=1 for row i of adj matrix
        */

        //curk1 is the unary adder that stores the k=1 constraint of the current row. 
        vi curk1 = k1(row[i], idx);
        // reverse(curk1.begin(), curk1.end());
        lex(topk1, curk1, idx);

        for(int j=1; j<=n;j++){
            if(i==j) continue;

            /*
                encode k=2 for row i , j
            */
            vi curk2additional = k2(row[i], row[j],  idx);

            // assert(curk2additional.size()==2*n);

            vi curk2; //curk2 is the concatenated vector for the current pair that will be used for k=2
            curk2.insert(curk2.end(), curk1.begin(), curk1.end());
            curk2.insert(curk2.end(), curk2additional.begin(), curk2additional.end());
            assert(curk2.size()==topk2.size());
            // assert(curk2.size()==3*n);

            /*
                compares the k=2 encoding of first two rows and current pair of rows. 
            */
            lexConditional(topk2, curk2, idx, flat(i, j));

            for(int k=1;k<=n;k++){
                if(i==k||j==k) continue;
                if(i==1&&j==2&&k==3) continue;
                vi curk3additional = k3(row[i], row[j], row[k], idx);

                vi curk3;
                curk3.insert(curk3.end(), curk2.begin(), curk2.end());
                curk3.insert(curk3.end(), curk3additional.begin(), curk3additional.end());
                int tmp = idx++;
                //tmp <-> flatij or flatjk or flatik
                //(¬Flatij ∨ Tmp) ∧ (¬Flatjk ∨ Tmp) ∧ (¬Flatik ∨ Tmp) ∧ (¬Tmp ∨ Flatij ∨ Flatjk ∨ Flatik)
                print2(-flat(i, j), tmp); print2(-flat(j, k), tmp); print2(-flat(i, k), tmp);
                print4(-tmp, flat(i, j), flat(i, k), flat(j, k));
                lexConditional(topk3, curk3, idx, tmp);
            }
        }
    }
    cout << endl;
    return 0;

}


