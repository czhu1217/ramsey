#include <algorithm>
#include <cassert>
#include <bitset>
#include <iterator>
#include <math.h>
#include <new>
#include <numeric>
#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <array>
#include <stdexcept>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <sstream>
using namespace std;
// #define DEBUG

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
//choose vertices
int n, l, k;
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

void lex(vi x, vi p, int start){
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

void lexConditional(vi x, vi p, int start, int k1){
    assert(x.size()==p.size());
    int l = x.size();
    cout << -x[0] << " " << p[0] << " 0\n";
    for(int i=0;i<l;i++){
        cout << -x[i] << " " << start+i << " 0\n";
        cout << p[i] << " " << start+i << " 0\n";
        cout << k1 << " ";
        for(int j=0;j<i;j++){
            cout << -1*(start+j) << " ";
        }
        cout << -x[i] << " " << p[i] << " 0\n";
    }

}
int k1(vector<int> a, int start){
    int ori = start;
    int l = a.size();
    vector<int> pre, cur;
    iff(start, a[0]);

    //the first array contains two elements: first variable 0, first variable 1
    pre.push_back(-1);
    pre.push_back(start++);
    #ifdef DEBUG
            for(auto e:pre) cout << e << " ";
            cout << "\n";
        #endif

    //loop all the i from 1 to a.size()-1
    for(int i = 1; i< a.size(); i++){
        cur.clear();
        cur.push_back(-1);
        //variable for if there's no 1 up until index i
        print2(-pre[1], start);
        print2(-a[i], start);
        print3(-start, pre[1], a[i]);
        cur.push_back(start++);
        
        //loop all the possible 1 count: 1 to i-1
        for(int j=2;j<=i;j++){
            int b = a[i], c = pre[j], d = pre[j-1];
            print2(-c, start);
            print3(-b, -d, start);
            print3(b, c, -start);
            print3(d, c, -start);
            cur.push_back(start++);
        }
        //cur[i] iff pre[i-1] and a[i]
        print2(-start, pre[i]);
        print2(-start, a[i]);
        print3(start, -pre[i], -a[i]);
        
        cur.push_back(start++);
        pre = cur;
        assert(pre.size()==i+2);


    }
    return start;
}


//returns a vector of 3 numbers: first for start of count of (1, 1) pairs, second for (0, 1) pairs, third for new start
vi k2(vi a, vi b, int st){
    vi ans, pre, cur;
    int l = a.size();
    
    //(0, 1) pairs
    //v[0][1]
    print3(a[0], -b[0], st);
    print2(-st, -a[0]);
    print2(-st, b[0]);
    pre.push_back(-1);
    pre.push_back(st++);

    //v[i][-i]
    for(int i=1;i<l;i++){
        cur.clear();
        cur.push_back(-1);
        //(¬Pre ∨ St) ∧ (A ∨ ¬B ∨ St) ∧ (¬A ∨ Pre ∨ ¬St) ∧ (B ∨ Pre ∨ ¬St)
        print2(-pre[1], st);
        print3(a[i], -b[i], st);
        print3(-a[i], pre[1], -st);
        print3(b[i], pre[1], -st);
        cur.push_back(st++);
        for(int j=2;j<=i;j++){
            print2(-pre[j], st);
            print4(-pre[j-1], a[i], -b[i], st);
            print3(pre[j-1], pre[j], -st);
            print3(-a[i], pre[j], -st);
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
    ans.push_back(st-a.size());

    //(1, 1) pairs
    //v[0][1]
    cur.clear(); pre.clear();
    print3(-a[0], -b[0], st);
    print2(-st, a[0]);
    print2(-st, b[0]);
    pre.push_back(-1);
    pre.push_back(st++);
    assert(pre.size()==2);

    //v[i][-i]
    for(int i=1;i<l;i++){
        assert(pre.size()==i+1);
        cur.clear();
        cur.push_back(-1);
        //v[i][1]
        //(¬Pre ∨ St) ∧ (A ∨ ¬B ∨ St) ∧ (¬A ∨ Pre ∨ ¬St) ∧ (B ∨ Pre ∨ ¬St)
        print2(-pre[1], st);
        print3(-a[i], -b[i], st);
        print3(a[i], pre[1], -st);
        print3(b[i], pre[1], -st);
        cur.push_back(st++);
        for(int j=2;j<=i;j++){
            print2(-pre[j], st);
            print4(-pre[j-1], -a[i], -b[i], st);
            print3(pre[j-1], pre[j], -st);
            print3(a[i], pre[j], -st);
            print3(b[i], pre[j], -st);
            cur.push_back(st++);
        }
        print4(-pre[i], -a[i], -b[i], st);
        print2(-st, pre[i]);
        print2(-st, a[i]);
        print2(-st, b[i]);
        cur.push_back(st++);
        pre = cur;
    }
    ans.push_back(st-a.size());
    ans.push_back(st);
    assert(ans.size()==3);
    return ans;
}

int checkEqual(vi a, vi b, int st){
    int l = a.size();
    vi va;
    for(int i=0;i<l;i++){
        //(¬A ∨ ¬B ∨ C) ∧ (A ∨ B ∨ C) ∧ (¬B ∨ A ∨ ¬C) ∧ (¬A ∨ B ∨ ¬C)
        print3(-a[i], -b[i], st); print3(a[i], b[i], st); print3(-b[i], a[i], -st); print3(-a[i], b[i], st);
        va.push_back(st++);
    }
    for(auto e:va){
        cout << -e << " ";
    }
    cout << st << " 0\n";
    for(auto e:va) print2(-st, e);
    st++;
    //st is one larger than the actual equal variable
    return st;
}

// int cardLeq(vi a, vi b, int st){
//     vi v;
//     for(int i=0;i<a.size();i++){
//         cout << 
//     }
//     return st-1;
// }
int main(int argc, char* argv[]){
    cout << "ok\n";
    //n is length and k is the number of colors, l is the length limit
    string outname = "maxedge";
    // scanf("%d %d %d", &n, &k, &l);
    string tmp;
    bool yeslex;
    n = stoi(argv[1]);
    k = stoi(argv[2]);
    l = stoi(argv[3]);
    yeslex = stoi(argv[4]);
    // n = 20; k = 5; l = 5; lex = 1;

    outname += to_string(n) + "_" + to_string(k) + + "_" + to_string(l) + "_" + to_string(yeslex) + ".out";
    #ifdef DEBUG
        printf("debug\n");
    #else 
        freopen(outname.c_str(), "w", stdout);
    #endif

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
        lex(v1, v2,  idx);
        idx += v1.size();
    }
    //count number of 1s in each row
    // cout << "idx " << idx << "\n";
    

    vector<vi> row;
    vector<int> offset; row.push_back(offset);
    for(int i=1;i<=n;i++){
        vi a;
        for(int j=1;j<=n;j++){
            a.push_back(flat(i, j));
        }
        row.push_back(a);
    }

        /*
        encode k=1 for first row
    */
    idx = k1(row[1], idx); //idx is the next available variable. We increase it after encoding k1 for first row of adj matrix
    int k1r1 = idx - n; //this is the first element of the unary counter
    vi topk1; //topk1 is the unary adder that stores the k=1 constraint of the 1st row. 
    for(int i=0;i<n;i++){
        topk1.push_back(k1r1+i);
    }

    /*
        encode k=2 additional constraints for first two rows
    */
    vi k2r1 = k2(row[1], row[2], idx); 
    //k2 returns a vector that contains [starting index of 1st counter, starting index of 2nd counter, index of next available variable]
    idx = k2r1[2];
    vi topk2; //topk2 is the unary adder that stores the k=2 additional constraint of row 1, 2. 
    for(int i=0;i<n;i++){
        topk2.push_back(k2r1[0]+i);
    }
    for(int i=0;i<n;i++){
        topk2.push_back(k2r1[1]+i);
    }

    /*
        Combine previous steps to produce a complete k=2 encoding
    */
    //top3 is the concatenated vector that will be used for ensuring k=2. It's topk1 concatenated with topk2
    vi top3; top3.reserve(topk1.size()+topk2.size());
    top3.insert(top3.end(), topk1.begin(), topk1.end());
    top3.insert(top3.end(), topk2.begin(), topk2.end());
    assert(top3.size()==3*n);


    for(int i=1;i<=n;i++){
        /*
            encode k=1 for row i of adj matrix
        */
        idx = k1(row[i], idx);
        int tmp = idx - n;

        //curk1 is the unary adder that stores the k=1 constraint of the current row. 
        vi curk1;
        for(int i=0;i<n;i++) curk1.push_back(tmp+i);
        vi a = row[i];

        for(int j=1; j<=n;j++){//no
            if(i==j) continue;
            if(i==1&&j==2) continue;

            /*
                encode k=2 for row i , j
            */
            vi b = row[j];
            vi v2 = k2(a, b, idx);
            assert(idx+(a.size()+1)*a.size()==v2[2]);
            idx = v2[2];
            vi curk2; //curk2 is the unary adder that stores the k=2 additional constraint of the current pair (a, b). 
            for(int k=0;k<n;k++){
                curk2.push_back(v2[0]+k);
            }
            for(int k=0;k<n;k++){
                curk2.push_back(v2[1]+k); 
            }
            assert(curk2.size()==2*n);

            vi cur3; //cur3 is the concatenated vector for the current pair that will be used for k=2
            cur3.insert(cur3.end(), curk1.begin(), curk1.end());
            cur3.insert(cur3.end(), curk2.begin(), curk2.end());
            assert(cur3.size()==top3.size());
            assert(cur3.size()==3*n);

            /*
                compares the k=2 encoding of first two rows and current pair of rows. 
            */
            lex(top3, cur3, idx);
            idx += top3.size();
        }
    }
    cout << endl;
    return 0;

}