#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> a, b;
    for(int i=1;i<=n;i++){
        int ai;
        cin >> ai;
        a.push_back(ai);
    }
    for(int i=1;i<=n;i++){
        int ai;
        cin >> ai;
        b.push_back(ai);
    }
    for(int i=0;i<n;i++){
        if(a[i]!=b[i]){ cout << "dif\n"; return 0;}
    }
    return 0;
}