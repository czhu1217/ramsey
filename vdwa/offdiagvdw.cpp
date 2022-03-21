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
    vector<int> nums;
    for(int i=0;i<k;i++){
        nums.push_back(stoi(argv[i+3]));
    }

    outname += to_string(n) + "_" + to_string(k) + + "_";
    for(int i=0;i<nums.size()-1;i++){
        outname += to_string(nums[i]) + "-";
    }
    outname += to_string(nums[nums.size()-1]) + ".cnf";
    freopen(outname.c_str(), "w", stdout);


    vector<vector<int>> vec2d;
    for(int i=0;i<n;i++){
        vector<int> v, vnot;
        for(int j=1;j<=k;j++){
            v.push_back(i*k+j);
            vnot.push_back(-1*(i*k+j));
        }
        vec2d.push_back(v);
        vec2d.push_back(vnot);
    }
    for(int s=1;s<=k;s++){
        l = nums[s-1];
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