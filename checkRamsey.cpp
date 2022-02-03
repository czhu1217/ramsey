#include <bits/stdc++.h>
using namespace std;
int n;
int flat(int a, int b){ return a*(n-1)+b;}
    vector<int> v;
bool check(vector<int> nodes, int lo, int hi){
    int cnt = 0;
    for(int i=0;i<nodes.size();i++){
        for(int j=i+1;j<nodes.size();j++){
            int a = nodes[i], b = nodes[j];
            if(v[flat(a, b)]>0) cnt++;
        }
    }
    if(cnt<lo || cnt > hi) return false;
    return true;
}
int main(){
    cin >> n;
    v.resize(n*n+1);
    for(int i=1;i<=n*n;i++){
        cin >> v[i];
    }
    vector<int> nodes;
    for(int i1 = 1;i1<=n;i1++){
        nodes.push_back(i1);
        for(int i2=i1+1;i2<=n;i2++){
            nodes.push_back(i2);
            for(int i3 = i2+1;i3<=n;i3++){
                nodes.push_back(i3);
                for(int i4 = i3+1;i4<=n;i4++){
                    nodes.push_back(i4);
                    for(int i5 = i4+1;i5<=n;i5++){
                        nodes.push_back(i5);
                        if(!check(nodes, 2, 9)){
                            cout << "wrong\n";
                            return 0;
                        }
                        nodes.pop_back();
                    }
                    nodes.pop_back();
                }
                nodes.pop_back();
            }
            nodes.pop_back();
        }
        nodes.pop_back();
    }
}