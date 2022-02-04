#include <bits/stdc++.h>
using namespace std;
int n, v[29*29+1];
int flat(int a, int b){ return (a-1)*n+b;}
int nc2(int n){
    return n*(n-1)/2;
}
bool check(vector<int> nodes, int lo, int hi){
    int cnt = 0;
    for(int i=0;i<nodes.size();i++){
        for(int j=i+1;j<nodes.size();j++){
            int a = nodes[i], b = nodes[j];
            if(v[flat(a, b)]<0) cnt++;
        }
    }
    if(cnt<lo || cnt > hi){
        // cout << "huh " << cnt << "\n";
        return false;
    } 
    return true;
}
int main(){
    cin >> n;
    int cnt = 1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> v[cnt];
            cnt++;
        }
    }
    cnt = 1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(v[cnt]<0){
                cout << "0 ";
            }
            else cout << "1 ";
            cnt++;
        }
        cout << "\n";
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
                        if(!check(nodes, 2, nc2(n)-1)){
                            for(int i=0;i<nodes.size();i++){
                                cout << nodes[i] << " ";
                            }
                            cout << "\n";
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
    cout << "okok!\n";
}