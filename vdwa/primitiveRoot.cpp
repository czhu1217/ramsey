#include <bits/stdc++.h>
using namespace std;
    vector<int> v;

int findPR(int n){
    cout << "finding pr of " << n << " \n";
    vector<bool> vis;
    vis.resize(n);
    int cnt = 1; bool works = true;
    for(int i=2;i<=(n);i++){
        works = true;
        for(int j=0;j<n;j++) vis[j] = 0;
        for(int j=1;j<n;j++){
            cnt *= i;
            cnt %= n;
            if(vis[cnt]){
                works = false;
                break;
            }
            else vis[cnt] = 1;
        }
        if(works) return i;
    }
    return 0;
}

bool isPrime(int p){
    for(int i=2;i<=sqrt(p);i++){
        if(p%i==0){
            return false;
        }
    }
    return true;
}
vector<int> getArray(int p, int r){
    vector<int> ans;
    int cnt = 1;
    for(int i=1;i<p;i++){
        cnt = (cnt*r)%p;
        ans.push_back(cnt);
    }
    return ans;
}

void fun(int p1){
    int pr = findPR(p1);        
        vector<int> ar = getArray(p1, pr);
        for(int i=0;i<ar.size();i++){
            int a = ar[i];
            if(v[a]<0) ar[i]*=-1;
        }
        for(auto e:ar) cout << e  << " ";
        cout << endl;
}


int main(){
    vector<int> ar, ar2;
    int n;
    cin >> n;
    v.push_back(0);
    for(int i=1;i<=n;i++){
        int a;
        cin >> a;
        v.push_back(a);
    }
    while(true){
        int p1;
        cin >> p1;
        fun(p1);
    }

    return 0;
}