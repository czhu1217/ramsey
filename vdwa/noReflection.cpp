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

int main(){
    int n, l;
    cin >> n >> l;
    vi a;
    vector<vi> v;
    int t;
    FOR(i, 1, n){
        vi vv;
        FOR(j, 1, l){
            cin >> t;
            vv.pb(t);
        }
        v.pb(vv);
    }
    vector<vi> ans;
    for(int i=0;i<v.size();i++){
        bool unique = true;
        for(int j=0;j<ans.size();j++){
            bool dif = false;
            for(int k=0;k<v[0].size();k++){
                if(v[i][k]*ans[j][ans[j].size()-1-k]<0){
                    dif = 1; break;
                }
            }
            if(!dif){
                unique = false;
                break;
            }
        }
        if(unique){ ans.push_back(v[i]); a.pb(i+1);}
    }

    for(auto e:a) cout << e << " ";
    cout << "\n";
    return 0;
}