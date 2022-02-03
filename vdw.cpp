#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int main(int argc, char* argv[]){
    //n is length and k is the number of colors, l is the length limit
    int n, k, l;
    string outname = "vdw";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l = stoi(argv[3]);

    outname += to_string(n) + "_" + to_string(k) + + "_" + to_string(l) + ".cnf";
    freopen(outname.c_str(), "w", stdout);
    cout << "c " << "vdw " << n << " " << k << " " << l << "\n";
    vector<vector<int>> vec2d;
    for(int i=0;i<n;i++){
        vector<int> v;
        for(int j=1;j<=k;j++){
            v.push_back(i*k+j);
        }
        vec2d.push_back(v);
    }
    for(int s=1;s<=k;s++){
        for(int i=0;i<=n-l;i++){
            for(int d=1;d<=(n-i-1)/(l-1);d++){
                vector<int> v;
                for(int j=0;j<(l);j++){
                    v.push_back(-1*((i+d*j)*k+s));
                }
                vec2d.push_back(v);
            }
        }
    }
    int clausecnt, varcnt;
    clausecnt = vec2d.size();
    varcnt = n*k;
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