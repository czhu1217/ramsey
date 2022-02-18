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

void print2(int a, int b){ cout << a << " " << b << " 0\n";}
void print3(int a, int b, int c){ cout << a << " " << b << " " << c << " 0\n";}
void iff(int a, int b){
    print2(a, -b);
    print2(-a, b);
}

int writeLex(vi a, vi b, int start){
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
    //not t3[i][j] || t2[i][j+1]
    for(int j=0;j<l-2;j++){
        cout << -1*(start3+j) << " " << start2 + j+1<< " 0 ";
    }

    return start3 + l-2;


}

int countOne(vector<int> a, int start){
    int l = a.size();
    //start means first variable is false;
    iff(start, -a[0]);
    //start+1 means first variable is true;
    iff(start+1, a[0]);

    vector<int> pre, cur;
    //the first array contains two elements: first variable 0, first variable 1
    pre.push_back(start); pre.push_back(start+1);
    start += 2;

    //loop all the i from 1 to a.size()-1
    for(int i = 1; i< a.size(); i++){
        cur.clear();
        //variable for if there's no 1 up until index i
        print2(-start, pre[0]);
        print2(-start, -a[1]);
        print3(start, -pre[0], a[1]);
        cur.push_back(start++); 

        //loop all the possible 1 count: 1 to i-1
        for(int j=1;j<i;j++){
            int b = a[i], c = pre[j], d = pre[j-1];
            print3(b, -c, start);
            print3(-b, -d, start);
            print3(d, -b, -start);
            print3(b, c, -start);
            print3(d, c, -start);
            cur.push_back(start++);
        }
        //cur[i] iff pre[i-1] and a[i]
        print2(-start, pre[i-1]);
        print2(-start, a[i]);
        print3(start, -pre[i-1], -a[i]);
        cur.push_back(start++);
        pre = cur;

    }
    return start;
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

void writeLexico(vector<int> Xs, vector<int>Ys, int l, int start){
    //Writes the additional variables representing xi = yi
    for(int i=0;i<l-1; i++){
        cout << -1 * Xs[i] << " " << -1 * Ys[i] << " " << (start+i) << " " << 0 << endl;
        cout << -1 * Xs[i] << " " << Ys[i] << " " << -1 * (start+i) << " " << 0 << endl;
        cout << Xs[i] << " " << -1 * Ys[i] << " " << -1 * (start+i) << " " << 0 << endl;
        cout << Xs[i] << " " << Ys[i] << " " << (start+i) << " " << 0 << endl;
    }

    //Writes the additional variables representing xi <= yi
    for(int i=0;i<l;i++){
        cout << -1 * Xs[i] << " " <<  Ys[i] << " " << -1 * (start+l-1+i) << " " << 0 << endl;
        cout << Xs[i] << " " << (start+l-1+i) << " " << 0 << endl;
        cout << -1 * Ys[i] << " " << (start+l-1+i) << " " << 0 << endl;
    }

    //Writes the additional variables representing start and ... and start + i
    for(int i=0;i<l-1;i++){
        for(int j=0;j<=i;j++){
            cout << -1 * (start+2*l-1+i) << " " << start+j << " " << 0 << endl; 
        }
        cout << (start+2*l-1+i) << " ";
        for(int j=0;j<=i;j++){
            cout << -1 * (start+j) << " ";
        }
        cout << 0 << endl;
    }

    //Write that x1 <= y1
    cout << start+l-1 << " " << 0 << endl;
    
    //Write that if x1 = y1 and x2 = y2 and ... and xi = yi then xi+1 <= yi+1 
    for(int i=1;i<l;i++){
        cout << -1 * (start+2*l-1+(i-1)) << " " << start+l-1+i << " " << 0 << endl;
    }
}
int main(int argc, char* argv[]){
    cout << "ok\n";
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
    //ensures symmetry
    for(int i=1;i<=n;i++){
        cout << -flat(i, i) << " 0\n";
        for(int j=1;j<=n;j++){
            cout << flat(i, j) << " " << -flat(j, i) << " 0\n";
            cout << -flat(i, j) << " " << flat(j, i) << " 0\n";
        }
    }
    int idx = n*n+1;
    for(int i=1;i<n;i++){
        vector<int> v1, v2;
        for(int j=1;j<=n;j++){
            if(i==j || i+1==j) continue; 
            v1.push_back(flat(i, j));
            v2.push_back(flat(i+1, j));
        }
         writeLexico(v1, v2, v1.size(), idx);
        idx += 3*(v1.size()) - 2;
        // idx += v1.size()-1 + v1.size()-1 + v1.size()-2;
    }
    //count number of 1s in each row
    // vector<int> cnt1;
    // cnt1.push_back(0);
    // for(int i=1;i<=n;i++){
    //     vector<int> v;
    //     for(int j=1;j<=n;j++){
    //         v.push_back(flat(i, j));
            
    //     }
    //     idx = countOne(v, idx);
    //     cnt1.push_back(idx-1-n);
    // }
    // vector<int> cntr1;
    // for(int i=0;i<=n;i++){
    //     cntr1.push_back(cnt1[1]+i);
    // }

    // for(int i=2;i<cnt1.size();i++){
    //     vector<int> cntri;
    //     for(int j=0;j<=n;j++){
    //         cntri.push_back(cnt1[i]+j);
    //     }
    //     //make sure that the lex of any other row 1 cnt is smaller or equal to row one (aka the 1 shows up at a later place)
    //     idx = writeLex(cntri, cntr1,  idx);
    // }


    cout << endl;
    return 0;

}