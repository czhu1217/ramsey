#include <bits/stdc++.h>
using namespace std;
// #define DEBUG

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
//choose vertices
int n, l, k;
int tt;
vector<vector<int>> vec2d;
vector<int> v;
void print2(int a, int b){ cout << a << " " << b << " 0\n";}
void print3(int a, int b, int c){ cout << a << " " << b << " " << c << " 0\n";}
void print4(int a, int b, int c, int d){ cout << a << " " << b << " " << c << " " << d << " 0\n";}
void iff(int a, int b){
    print2(a, -b);
    print2(-a, b);
}
int flat(int i, int j){ return (i-1)*n+j; }

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
    //not t3[j] || t2[j]
    for(int j=0;j<l-2;j++){
        cout << -1*(start3+j) << " " << start2 + j+1<< " 0 ";
    }
    return start3 + l - 2;


}

int countOne(vector<int> a, int start){
    int l = a.size();
    #ifdef DEBUG
    #else
    //start means first variable is false;
    iff(start, -a[0]);
    //start+1 means first variable is true;
    iff(start+1, a[0]);
    #endif
    vector<int> pre, cur;
    //the first array contains two elements: first variable 0, first variable 1
    pre.push_back(start); pre.push_back(start+1);
    start += 2;
    #ifdef DEBUG
            for(auto e:pre) cout << e << " ";
            cout << "\n";
        #endif

    //loop all the i from 1 to a.size()-1
    for(int i = 1; i< a.size(); i++){
        if(i==a.size()-1) tt = start;
        cur.clear();
        //variable for if there's no 1 up until index i
        #ifdef DEBUG
        #else
            print2(-start, pre[0]);
            print2(-start, -a[i]);
            print3(start, -pre[0], a[i]);
        #endif

            cur.push_back(start++);
 
        

        //loop all the possible 1 count: 1 to i-1
        for(int j=1;j<=i;j++){
            int b = a[i], c = pre[j], d = pre[j-1];
            #ifdef DEBUG
            #else
                        print3(b, -c, start);
                print3(-b, -d, start);
                print3(d, -b, -start);
                print3(b, c, -start);
                print3(d, c, -start);
            #endif
            cur.push_back(start++);
        }
        //cur[i] iff pre[i-1] and a[i]
        #ifdef DEBUG
        #else
        print2(-start, pre[i]);
        print2(-start, a[i]);
        print3(start, -pre[i], -a[i]);
        #endif
        
        cur.push_back(start++);
        pre = cur;
        assert(pre.size()==i+2);
        #ifdef DEBUG
            for(auto e:pre) cout << e << " ";
            cout << "\n";
        #endif


    }
    return start;
}

int countTriple(vi a, vi b, vi c, int sa, int sb, int sc, int st, vi &pre, vi &cur){
    //v[0][1]
    print2(-st, -a[0]);
    print2(-st, -b[0]);
    print2(-st, c[0]);
    print4(a[0], b[0], -c[0], st);
    pre.push_back(st++);

    //v[i][1-i]
    for(int i=1;i<=l;i++){
        cur.clear();
        cur.push_back(-1);
        //v[i][1]: st1 <-> pre1 or (not a and not b and c)
        print2(-pre[1], st);
        print4(a[i], b[i], -c[i], st);
        print3(-a[i], pre[1], -st);
        print3(-b[i], pre[1], -st);
        print3(c[i], pre[1], -st);
        cur.push_back(st++);
        //v[i][j] <-> pre[j] or (pre[j-1] and ((not a) and (not b) and c))
        //(¬Prej ∨ St) ∧ (¬Prej1 ∨ A ∨ B ∨ ¬C ∨ St) ∧ (Prej1 ∨ Prej ∨ ¬St) ∧ (¬A ∨ Prej ∨ ¬St) ∧ (¬B ∨ Prej ∨ ¬St) ∧ (C ∨ Prej ∨ ¬St)
        for(int j=2;j<i;j++){
            print2(-pre[j], st);
            cout << pre[j-1] << " " << a[i] << " " << b[i] << " " << -c[i] << " " << st << " 0\n";
            print3(pre[j-1], pre[j], -st);
            print3(-a[i], pre[j], -st);
            print3(-b[i], pre[j], -st);
            print3(c[i], pre[j], -st);
            cur.push_back(st++);
        }

        //v[i][i] <-> pre[i-1] and ((not a) and (not b) and c))
        cout << -pre[i-1] << " " << a[i] << " " << b[i] << " " << -c[i] << " " << st << " 0\n";
        print2(-st, pre[i-1]);
        print2(-st, -a[i]);
        print2(-st, -b[i]);
        print2(-st, c[i]);
        pre = cur;
        
    }
}

vi k3(vi a, vi b, vi c, int st){
    vi ans;
    //count the number of 1s in the first row. or number of pairs of (1, {1, 0}, {1, 0})
    int l = a.size();

    //k=1
    st = countOne(a, st);
    ans.push_back(st);

    //k=2
    vi pre, cur;
    //count the number of pairs of (0, 1, 0) and (0, 1, 1)
    //v[i][j]: at least j pairs of (0, 1, _) up at index i
    //v[0][0]
    print3(-st, a[0], -b[0]);
    print2(st, -a[0]);
    print2(st, b[0]);
    pre.push_back(st++);

    //v[0][1]
    print3(a[0], -b[0], st);
    print2(-st, -a[0]);
    print2(-st, b[0]);
    pre.push_back(st++);

    //v[i][0-i]
    for(int i=1;i<=l;i++){
        cur.clear();
        //v[i][0]
        iff(st, pre[0]);
        cur.push_back(st++);
        for(int j=1;j<i;j++){
            print2(-pre[j], st);
            print4(-pre[j-1], a[i], -b[i], st);
            print3(pre[j-1], pre[j], -st);
            print3(-a[i], pre[j], st);
            print3(b[i], pre[j], -st);
            cur.push_back(st++);
        }
        print4(-pre[i], a[i], -b[i], st);
        print2(-st, pre[i]);
        print2(-st, -a[i]);
        print2(-st, b[i]);
        cur.push_back(st++);
        pre = cur;
    }
    ans.push_back(st);

    //k=3
    pre.clear(); cur.clear()

    //encode number of (0, 0, 1)
    //v[0][1]
    print2(-st, -a[0]);
    print2(-st, -b[0]);
    print2(-st, c[0]);
    print4(a[0], b[0], -c[0], st);
    pre.push_back(st++);

    //v[i][1-i]
    for(int i=1;i<=l;i++){
        cur.clear();
        cur.push_back(-1);
        //v[i][1]: st1 <-> pre1 or (not a and not b and c)
        print2(-pre[1], st);
        print4(a[i], b[i], -c[i], st);
        print3(-a[i], pre[1], -st);
        print3(-b[i], pre[1], -st);
        print3(c[i], pre[1], -st);
        cur.push_back(st++);
        //v[i][j] <-> pre[j] or (pre[j-1] and ((not a) and (not b) and c))
        //(¬Prej ∨ St) ∧ (¬Prej1 ∨ A ∨ B ∨ ¬C ∨ St) ∧ (Prej1 ∨ Prej ∨ ¬St) ∧ (¬A ∨ Prej ∨ ¬St) ∧ (¬B ∨ Prej ∨ ¬St) ∧ (C ∨ Prej ∨ ¬St)
        for(int j=2;j<i;j++){
            print2(-pre[j], st);
            cout << pre[j-1] << " " << a[i] << " " << b[i] << " " << -c[i] << " " << st << " 0\n";
            print3(pre[j-1], pre[j], -st);
            print3(-a[i], pre[j], -st);
            print3(-b[i], pre[j], -st);
            print3(c[i], pre[j], -st);
            cur.push_back(st++);
        }

        //v[i][i] <-> pre[i-1] and ((not a) and (not b) and c))
        cout << -pre[i-1] << " " << a[i] << " " << b[i] << " " << -c[i] << " " << st << " 0\n";
        print2(-st, pre[i-1]);
        print2(-st, -a[i]);
        print2(-st, -b[i]);
        print2(-st, c[i]);
        pre = cur;
        
    }
    //encode number of (0, 1, 1)
    pre.clear(); cur.clear();
    //v[0][1]
    print2(-st, -a[0]);
    print2(-st, b[0]);
    print2(-st, c[0]);
    print4(a[0], -b[0], -c[0], st);
    pre.push_back(st++);

    //v[i][1-i]
    for(int i=1;i<=l;i++){
        cur.clear();
        cur.push_back(-1);
        //v[i][1]: st1 <-> pre1 or (not a and not b and c)
        print2(-pre[1], st);
        print4(a[i], -b[i], -c[i], st);
        print3(-a[i], pre[1], -st);
        print3(b[i], pre[1], -st);
        print3(c[i], pre[1], -st);
        cur.push_back(st++);
        //v[i][j] <-> pre[j] or (pre[j-1] and ((not a) and (not b) and c))
        //(¬Prej ∨ St) ∧ (¬Prej1 ∨ A ∨ B ∨ ¬C ∨ St) ∧ (Prej1 ∨ Prej ∨ ¬St) ∧ (¬A ∨ Prej ∨ ¬St) ∧ (¬B ∨ Prej ∨ ¬St) ∧ (C ∨ Prej ∨ ¬St)
        for(int j=2;j<i;j++){
            print2(-pre[j], st);
            cout << pre[j-1] << " " << a[i] << " " << -b[i] << " " << -c[i] << " " << st << " 0\n";
            print3(pre[j-1], pre[j], -st);
            print3(-a[i], pre[j], -st);
            print3(b[i], pre[j], -st);
            print3(c[i], pre[j], -st);
            cur.push_back(st++);
        }

        //v[i][i] <-> pre[i-1] and ((not a) and (not b) and c))
        cout << -pre[i-1] << " " << a[i] << " " << -b[i] << " " << -c[i] << " " << st << " 0\n";
        print2(-st, pre[i-1]);
        print2(-st, -a[i]);
        print2(-st, b[i]);
        print2(-st, c[i]);
        pre = cur;
        
    }

    
    //encode number of (1, 0, 1)
    pre.clear(); cur.clear();
    //v[0][1]
    print2(-st, a[0]);
    print2(-st, -b[0]);
    print2(-st, c[0]);
    print4(-a[0], b[0], -c[0], st);
    pre.push_back(st++);

    //v[i][1-i]
    for(int i=1;i<=l;i++){
        cur.clear();
        cur.push_back(-1);
        //v[i][1]: st1 <-> pre1 or (not a and not b and c)
        print2(-pre[1], st);
        print4(-a[i], b[i], -c[i], st);
        print3(a[i], pre[1], -st);
        print3(-b[i], pre[1], -st);
        print3(c[i], pre[1], -st);
        cur.push_back(st++);
        //v[i][j] <-> pre[j] or (pre[j-1] and ((not a) and (not b) and c))
        //(¬Prej ∨ St) ∧ (¬Prej1 ∨ A ∨ B ∨ ¬C ∨ St) ∧ (Prej1 ∨ Prej ∨ ¬St) ∧ (¬A ∨ Prej ∨ ¬St) ∧ (¬B ∨ Prej ∨ ¬St) ∧ (C ∨ Prej ∨ ¬St)
        for(int j=2;j<i;j++){
            print2(-pre[j], st);
            cout << pre[j-1] << " " << -a[i] << " " << b[i] << " " << -c[i] << " " << st << " 0\n";
            print3(pre[j-1], pre[j], -st);
            print3(a[i], pre[j], -st);
            print3(-b[i], pre[j], -st);
            print3(c[i], pre[j], -st);
            cur.push_back(st++);
        }

        //v[i][i] <-> pre[i-1] and ((not a) and (not b) and c))
        cout << -pre[i-1] << " " << -a[i] << " " << b[i] << " " << -c[i] << " " << st << " 0\n";
        print2(-st, pre[i-1]);
        print2(-st, a[i]);
        print2(-st, -b[i]);
        print2(-st, c[i]);
        pre = cur;
        
    }

    //encode number of (1, 1 ,1)
    //v[0][1]
    print2(-st, a[0]);
    print2(-st, b[0]);
    print2(-st, c[0]);
    print4(-a[0], -b[0], -c[0], st);
    pre.push_back(st++);

    //v[i][1-i]
    for(int i=1;i<=l;i++){
        cur.clear();
        cur.push_back(-1);
        //v[i][1]: st1 <-> pre1 or (not a and not b and c)
        print2(-pre[1], st);
        print4(-a[i], -b[i], -c[i], st);
        print3(a[i], pre[1], -st);
        print3(b[i], pre[1], -st);
        print3(c[i], pre[1], -st);
        cur.push_back(st++);
        //v[i][j] <-> pre[j] or (pre[j-1] and ((not a) and (not b) and c))
        //(¬Prej ∨ St) ∧ (¬Prej1 ∨ A ∨ B ∨ ¬C ∨ St) ∧ (Prej1 ∨ Prej ∨ ¬St) ∧ (¬A ∨ Prej ∨ ¬St) ∧ (¬B ∨ Prej ∨ ¬St) ∧ (C ∨ Prej ∨ ¬St)
        for(int j=2;j<i;j++){
            print2(-pre[j], st);
            cout << pre[j-1] << " " << -a[i] << " " << -b[i] << " " << -c[i] << " " << st << " 0\n";
            print3(pre[j-1], pre[j], -st);
            print3(a[i], pre[j], -st);
            print3(b[i], pre[j], -st);
            print3(c[i], pre[j], -st);
            cur.push_back(st++);
        }

        //v[i][i] <-> pre[i-1] and ((not a) and (not b) and c))
        cout << -pre[i-1] << " " << -a[i] << " " << -b[i] << " " << -c[i] << " " << st << " 0\n";
        print2(-st, pre[i-1]);
        print2(-st, a[i]);
        print2(-st, b[i]);
        print2(-st, c[i]);
        pre = cur;
        
    }

}
void addEdges(int sign){
    int a, b;
    vector<int> tmp;
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            // if(i==j) continue;
            a = v[i]; b = v[j];
            #ifdef DEBUG
            #else
            cout << sign*flat(a, b)<< " ";
            #endif
            // cout << sign*((b-1)*n+a) << " ";
        }
    }
    #ifdef DEBUG
    #else
    cout << " 0\n";
    #endif
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
    #ifdef DEBUG
    #else
    for(int i=0;i<tmp.size();i++){
        for(int j=0;j<tmp.size();j++){
            if(j==i) continue;
            cout << tmp[j] << " ";
        }
        cout << "0\n";
    }
    #endif
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

void lex2(vi x, vi p, int start){
    assert(x.size()==p.size());
    int l = x.size();
    cout << -x[0] << " " << p[0] << " 0\n";
    for(int i=0;i<l;i++){
        cout << -x[i] << " " << start+i << " 0\n";
        cout << p[i] << " " << start+i << " 0\n";
        for(int j=0;j<i;j++){
            cout << -1*(start+j) << " ";
        }
        cout << -x[i] << " " << p[i] << " 0\n";
    }

}

int main(int argc, char* argv[]){
    cout << "ok\n";
    //n is length and k is the number of colors, l is the length limit
    string outname = "maxedge";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    bool lex;
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l = stoi(argv[3]);
    lex = stoi(argv[4]);
    // n = 20; k = 5; l = 5; lex = 1;

    outname += to_string(n) + "_" + to_string(k) + + "_" + to_string(l) + "_" + to_string(lex) + ".out";
    #ifdef DEBUG
        printf("debug\n");
    #else 
        freopen(outname.c_str(), "w", stdout);
    #endif

    pickV(1, k, 1);
    pickV(1, l, -1);
    //ensures symmetry
    #ifdef DEBUG
    #else
    for(int i=1;i<=n;i++){
        cout << -flat(i, i) << " 0\n";
        for(int j=1;j<=n;j++){
            cout << flat(i, j) << " " << -flat(j, i) << " 0\n";
            cout << -flat(i, j) << " " << flat(j, i) << " 0\n";
        }
    }
    if(!lex){
        cout << endl;
        return 0;
    }
    #endif
    int idx = n*n+1;

    for(int i=1;i<n;i++){
        vector<int> v1, v2;
        for(int j=1;j<=n;j++){
            if(i==j || i+1==j) continue; 
            v1.push_back(flat(i, j));
            v2.push_back(flat(i+1, j));
        }
        lex2(v1, v2, idx);
        idx += v1.size();
    }
    //count number of 1s in each row
    // cout << "idx " << idx << "\n";
    vector<int> cnt1;
    cnt1.push_back(0);
    for(int i=1;i<=n;i++){
        vector<int> v;
        for(int j=1;j<=n;j++){
            v.push_back(flat(i, j));
            
        }
        for(auto e:v)
        idx = countOne(v, idx);
        cnt1.push_back(idx-1-n);
        // cout << "sldkflskjfds\n";
        // cout << tt << "\n";
        assert(idx-1-n==tt);
        
    }
    vector<int> cntr1;
    for(int i=0;i<=n;i++){
        cntr1.push_back(cnt1[1]+i);
    }
    assert(cntr1.size()==n+1);
    #ifdef DEBUG
        for(auto e:cntr1) cout << e << " ";
        cout << "\n";
    #endif

    for(int i=2;i<cnt1.size();i++){
        vector<int> cntri;
        for(int j=0;j<=n;j++){
            cntri.push_back(cnt1[i]+j);
        }
        #ifdef DEBUG
            for(auto e:cntri) cout << e << " " ;
            cout << "\n";
        #endif
        assert(cntri.size()==n+1);
        //make sure that the lex of any other row 1 cnt is smaller or equal to row one (aka the 1 shows up at a later place)
        #ifdef DEBUG
        #else
        // cout << "asjdhkads " << cntr1[0] << " " << cntri[0] << "\n";
        assert(cntri.size()==cntr1.size());
        lex2( cntri, cntr1,  idx);
        idx += cntri.size();
        #endif
    }
    cout << endl;
    return 0;

}