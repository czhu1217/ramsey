#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    vector<int> v;
    int a;
    while(cin >> a){
        v.push_back(a);
    }
    for(int i=0;i<v.size();i++){
        cout << -v[i] << " ";
    }
    cout << " 0\n";
    return 0;
}