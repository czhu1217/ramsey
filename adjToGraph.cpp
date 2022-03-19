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

int adj[100][100];

int main(int argc, char* argv[]){
    string inname = argv[1];
    int n = stoi(argv[2]);
    string outname = "v" + to_string(n) + "g6.g6";

    freopen(inname.c_str(), "r", stdin);
    freopen(outname.c_str(), "w", stdout);

    string st;
    while(cin >> st){
        vi ans;
        vi bitv;
        int cnt = 0;
        FOR(i, 0, n-1) FOR(j, 0, n-1) adj[i][j] = st[cnt++]-'0';
        // FOR(i, 0, n-1){ FOR(j, 0, n-1){ cout << adj[i][j] << " " ; }cout << "\n";}
        FOR(j, 1, n-1) FOR(i, 0, j-1){bitv.push_back(adj[i][j]);}
        // for(auto e:bitv) cout << e << " ";
        // cout << "\n";
        int N = n+63;
        ans.push_back(N);
        int nn = ceil((bitv.size()*1.0)/6);
        // cout << nn << "\n";
        while(bitv.size()<nn*6) bitv.push_back(0);
        FOR(i, 0, nn-1){
            int tmp = 0;
            FOR(j, 0, 5){
                int idx = i*6+j;
                tmp += bitv[idx]*pow(2, 5-j);
            }
            ans.push_back(tmp+63);
        }
        // for(auto e:ans) cout << e <<  " ";
        // cout << "\n";
        vector<char> ansc;
        for(auto e:ans) {ansc.push_back((char) e);}
        for(auto e:ansc) cout << e;
        cout << "\n";
    }
    
    


}