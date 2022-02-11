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

void writeLex(vi a, vi b, int start){
    int l = a.size();
    cout << -a[0] << " " << b[0] << " 0\n";
    //a[i] = b[i]
    for(int i=0;i<l-1;i++){
        cout << -1*a[i] << " " << b[i] << " " << -1*(start+i) << " 0\n";
        cout << a[i] << " " << -1*b[i] << " " << -1*(start+i) << " 0\n";
        cout << a[i] << " " << b[i] << " " << (start+i) << " 0\n";
        cout << -a[i] << " " << -b[i] << " " << start+i << " 0\n";
    }
    int start2 = start + l-1;
    //a[i+1] <= b[i+1]
    for(int i=0;i<l-1;i++){
        cout << a[i+1] << " " << start2+i << " 0\n";
        cout << -b[i+1] << " " << start2+i << " 0\n";
        cout << a[i+1] << " " << b[i+1] << " " << start2+i << " 0\n";
    }
    int start3 = start2 + l-1;
    // encode t3

    for(int i=0; i<l-2;i++){
        cout << start3+i << " ";
        for(int j=0;j<=i+1;j++){
            cout << start + j << " ";
        }
        cout << " 0\n";
        for(int j=0;j<=i+1;j++){
            cout << -1*(start3+i) << " " << start+j << " 0\n";
        }
    }


    cout << -1*(start) << " " << start2 << " 0 ";
    //not t3[j] || t2[j]
    for(int j=0;j<l-2;j++){
        cout << -1*(start3+j) << " " << start2 + j+1<< " 0 ";
    }


}
//AND method lex ordering (1st in the paper)
int lex_order(int i, int start){
    // cout << start << " 0 ";
    //adj[i][1] <= adj[i+1][1]
    cout << -flat(i, 1) << " " << flat(i+1, 1) << " 0 ";
    //encode t1: adj[i][j] = adj[i+1][j] using extra variable at the end
    for(int j=1;j<n;j++){
        cout << -flat(i, j) << " " << flat(i+1, j) << " " << -1*( start + j) << " 0 ";
        cout << flat(i, j) << " " << -flat(i+1, j) << " " << -1*(start + j) << " 0 ";
        cout << flat(i, j) << " " << flat(i+1, j) << " " << (start + j) << " 0 ";
        cout << -flat(i, j) << " " << -flat(i+1, j) << " " << (start + j) << " 0 ";
    }

    int start2 = start + n-1;
    // //encode t2: adj[i][j] <= adj[i+1][j];
    for(int j=1;j<n;j++){
        cout << flat(i, j+1) << " " << start2 + j<< " 0 ";
        cout << -flat(i+1, j+1) << " " << start2 + j << " 0 ";
        cout << -flat(i, j+1) << " " << flat(i+1, j+1) << " " << -1*(start2+j) << " 0 ";
    }

    int start3 = start2 + n-1;
    //encode t3
    cout << start3 + 1 << " " << -1*(start + 1) << " 0\n";
    cout << -1*(start3 + 1) << " " << start + 1 << " 0\n";
    cout << start3 + 1 << " " << -1*(start + 2) << " 0\n";
    cout << -1*(start3 + 1) << " " << start + 2 << " 0\n";
    // for(int j=2;j<=n-2;j++){
    //     cout << -1*(start3 + j )<< " " << start3 + j-1 << " 0\n";
    //     cout << -1*(start3 + j ) << " " << start + j + 1 << " 0\n";
    //     cout << start3 + j << " " << -1*(start3+j-1) << " " << -1*(start+j+1) << " 0\n";
    // }

    
    //not t1[i][1] || t2[i][1]
    cout << -1*(start + 1) << " " << start2 + 1 << " 0 ";

    //not t3[i][j] || t2[i][j+1]
    // for(int j=1;j<=n-2;j++){
    //     cout << -1*(start3+j) << " " << start2 + j+1<< " 0 ";
    // }

    return start3 + n-2;
}

void addEdges(int sign){
    int a, b;
    vector<int> tmp;
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            // if(i==j) continue;
            a = v[i]; b = v[j];
            cout << sign*flat(a, b)<< " ";
            // cout << sign*((b-1)*n+a) << " ";
        }
    }
    cout << " 0\n";
}

void addEdges2(int sign){
    int a, b;
    vector<int> tmp;
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            // if(i==j) continue;
            a = v[i]; b = v[j];
            // cout << sign*flat(a, b)<< " ";
            // cout << sign*((b-1)*n+a) << " ";
            tmp.push_back(sign*flat(a, b));
        }
    }
    // cout << "tmp " << tmp.size() << "\n";
    for(int i=0;i<tmp.size();i++){
        for(int j=0;j<tmp.size();j++){
            if(j==i) continue;
            cout << tmp[j] << " ";
        }
        cout << "0\n";
    }
}

void pickV(int cur,int m, int sign){
    if(v.size()==m){
        addEdges2(sign);
        return;
    }
    if(cur>n) return;
    v.push_back(cur);
    pickV(cur+1, m, sign);
    v.pop_back();
    pickV(cur+1, m, sign);
}

int main(int argc, char* argv[]){
    cout << "ok\n";
    //n is length and k is the number of colors, l is the length limit
    string outname = "maxedge";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l = stoi(argv[3]);
    bool lex = stoi(argv[4]);

    outname += to_string(n) + "_" + to_string(k) + + "_" + to_string(l) + "_" + to_string(lex) + ".out";
    freopen(outname.c_str(), "w", stdout);
    pickV(1, k, 1);
    pickV(1, l, -1);
    //ensures symmetry
    for(int i=1;i<=n;i++){
        cout << -flat(i, i) << " 0\n";
        for(int j=1;j<=n;j++){
            cout << flat(i, j) << " " << -flat(j, i) << " 0\n";
            cout << -flat(i, j) << " " << flat(j, i) << " 0\n";
        }
    }
    int idx = n*n+1;
    if(!lex){
        cout << endl;
        return 0;
    }
    for(int i=1;i<n;i++){
        vector<int> v1, v2;
        for(int j=1;j<=n;j++){
            if(i==j || i+1==j) continue; 
            v1.push_back(flat(i, j));
            v2.push_back(flat(i+1, j));
        }
        writeLex(v1, v2,  idx);
        idx += v1.size()-1 + v1.size()-1 + v1.size()-2;
    }
    cout << endl;
    return 0;

}