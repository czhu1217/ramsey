#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
//choose vertices
int n, l, k;
vector<vector<int>> vec2d;
vector<int> v;

int flat(int i, int j){ return (i-1)*n+j; }
//AND method lex ordering (1st in the paper)
void lex_order(int i){
    //encode t1: adj[i][j] = adj[i+1][j] using extra variable at the end
    int start = n*n;
    for(int j=1;j<=n;j++){
        cout << -flat(i, j) << " " << flat(i+1, j) << " " << -1*( start + flat(i, j)) << " 0 ";
        cout << flat(i, j) << " " << -flat(i+1, j) << " " << -1*(start + flat(i, j)) << " 0 ";
        cout << flat(i, j) << " " << flat(i+1, j) << " " << (start + flat(i, j)) << " 0 ";
        cout << -flat(i, j) << " " << -flat(i+1, j) << " " << (start + flat(i, j)) << " 0 ";
    }

    int start2 = start + (n-1)*n;
    //encode t2: adj[i][j] <= adj[i+1][j];
    for(int j=1;j<=n;j++){
        cout << flat(i, j) << " " << start2 + flat(i, j) << " 0 ";
        cout << -flat(i+1, j) << " " << start2 + flat(i, j) << " 0 ";
        cout << -flat(i, j) << " " << flat(i, j) << " " << -1*(start2+flat(i, j)) << " 0 ";
    }

    int start3 = start2 + (n-1)*n;
    //encode t3
    cout << start3 + flat(i, 1) << " " << -1*(start + flat(i, 1)) << " 0 ";
    cout << -1*(start3 + flat(i, 1)) << " " << start + flat(i, 1) << " 0 ";
    for(int j=2;j<=n;j++){
        cout << -1*(start3 + flat(i, j)) << " " << start3 + flat(i, j-1) << " 0 ";
        cout << -1*(start3 + flat(i, j)) << " " << start + flat(i, j) << " 0 ";
        cout << -1*(start3 + flat(i, j-1)) << " " << -1*(start+flat(i, j)) << " " << start3 + flat(i ,j) << " 0 ";
    }

    //adj[i][1] <= adj[i+1][1]
    cout << start2 + flat(i, 1) << " 0 ";
    //not t1[i][1] || t2[i][2]
    cout << -1*(start + flat(i, 1)) << " " << start2 + flat(i, 2) << " 0 ";

    //not t3[i][j] || t2[i][j+2]
    for(int j=1;j<=n-2;j++){
        cout << -1*(start3+flat(i, j)) << " " << start2 + flat(i, j+2) << " 0 ";
    }
    
    
}

void addEdges(int sign){
    int a, b;
    vector<int> tmp;
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            a = v[i]; b = v[j];
            cout << sign*((a-1)*n+b) << " ";
        }
    }
    cout << " 0 ";
}

void pickV(int cur,int m, int sign){
    if(v.size()==m){
        addEdges(sign);
        return;
    }
    if(cur>n) return;
    v.push_back(cur);
    pickV(cur+1, m, sign);
    v.pop_back();
    pickV(cur+1, m, sign);
}
int main(int argc, char* argv[]){
    //n is length and k is the number of colors, l is the length limit
    string outname = "ramsey";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l = stoi(argv[3]);

    outname += to_string(n) + "_" + to_string(k) + + "_" + to_string(l) + ".out";
    freopen(outname.c_str(), "w", stdout);
    pickV(1, k, 1);
    pickV(1, l, -1);
    // for(int i=1;i<n;i++) lex_order(i);
    cout << endl;
    return 0 ;

}