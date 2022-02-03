#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int main(int argc, char* argv[]){
    //n is length and k is the number of colors, l is the length limit
    int n, k, l1, l2;
    string outname = "vdw2c";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l1 = stoi(argv[3]);
    l2 = stoi(argv[4]);

    outname += to_string(n) + "_" + to_string(k) + + "_" + to_string(l1) + "-"  +  to_string(l2) + ".cnf";
    freopen(outname.c_str(), "w", stdout);
    cout << "c " << "vdw " << n << " " << k << " " << l1 << " " << l2 << "\n";
    vector<vector<int>> vec2d;

        for(int i=1;i<=n;i++){
        for(int d=1;d<=n;d++){
            if(i+d*(l2-1)>n) break;
            vector<int> v;
            for(int j=0;j<l2;j++){
                v.push_back(-1*(i+j*d));
            }
            vec2d.push_back(v);
        }
    }
    
    for(int i=1;i<=n;i++){
        for(int d=1;d<=n;d++){
            if(i+d*(l1-1)>n) break;
            vector<int> v;
            for(int j=0;j<l1;j++){
                v.push_back(i+j*d);
            }
            vec2d.push_back(v);
        }
    }



    int clausecnt, varcnt;
    clausecnt = vec2d.size();
    varcnt = n;
    cout << "p cnf " << varcnt << " " << clausecnt << "\n";
    for(auto v:vec2d){
        for(auto e:v){
            cout << e << " ";
        }
        cout << "0\n";
    }
    cout << endl;
    return 0;


}