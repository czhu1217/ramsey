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
    int n;
    cin >> n;
    while(true){
        vi v;
        v.pb(-1);
        int tmp;
        FOR(i, 1, n){
            cin >> tmp;
            v.pb(tmp);
        }
        int md = 1;
        int cnt = 0;
        while(md++<=n){
            FOR(k, 1, n){
                if(k+md*2>n) break;
                // if(k>0&&k+md-1>0&&k+md+1>0&&k+md*2>0) cnt++;
                if(v[k]<=0&&v[k+md-1]<=0&&v[k+md+1]<=0&&v[k+md*2]<=0) cnt++;
            }
            if(cnt!=0){
                cout << cnt << " donuts " << " at mod " << md << "\n";
                cnt = 0;
            }
        }

    }
    
    // cout << cnt << "\n";
    return 0;

}