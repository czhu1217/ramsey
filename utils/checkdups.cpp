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

int main(){
    cout << "hi\n";
    int n = 15;
    int len = n*n;
    vector<vi> v;
    int k;
    vi tmp;
    bool ac = true;
    int cnt = 0;
    while(cin>>k){
        cnt++;
        tmp.pb(k);
        if(cnt==n*n){
            v.pb(tmp);
            // FOR(i, 0, tmp.size()){
            //     cout <<  << " ";
            // }
            // cout << "\n";

            tmp.clear();
            cnt = 0;
        }
    }
    FOR(i, 0, v.size()-1){
        FOR(j, i+1, v.size()-1){
            assert(v[j].size()==v[i].size());
            bool same = 1;
            FOR(m, 0, v[i].size()-1){
                if(v[i][m] != v[j][m]) same = 0;
            }
            if(same){
                cout << "same: " << i << " " << j << " \n";
            }
        }
    }
}