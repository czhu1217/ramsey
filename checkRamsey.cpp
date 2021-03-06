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
int n, v[4000];
int flat(int a, int b) { return (a - 1) * n + b; }
int nc2(int n)
{
    return n * (n - 1) / 2;
}
bool checkNeg(vector<int> nodes, int lo, int hi)
{
    int cnt = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
        {
            int a = nodes[i], b = nodes[j];
            if (v[flat(a, b)] <= 0)
                // cout << a << " " << b << " " << v[flat(a, b)] << " " << flat(a, b) << "\n";
                cnt++;
        }
    }
    // cout << "neg " << cnt << "\n";

    if (cnt < lo || cnt > hi)
    {
        return false;
    }
    return true;
}
bool checkPos(vector<int> nodes, int lo, int hi)
{
    int cnt = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
        {
            int a = nodes[i], b = nodes[j];
            if (v[flat(a, b)] > 0)
                cnt++;
        }
    }
    // cout << "pos " << cnt << "\n";
    if (cnt < lo || cnt > hi)
    {
        return false;
    }
    return true;
}
int main()
{
    int round = 0;
    n = 15;
    while(true)
    {
        cout << ++round << "\n";
        int cnt = 1;
        int tm;
        for (int i = 1; i <= n; i++)
        {
            // cout << "huh\n";
            for (int j = 1; j <= n; j++)
            {
                char c;
                cin >> tm; 
                // cout << tm << " ";
                // cout << tm << " ";
                v[cnt] = tm;
                cnt++;
            }
        }
        // for(int i=1;i<=n*n;i++){
        //     cout << v[i] << " ";
        // }
        cout << "\n";
        cnt = 1;
        vector<int> cntr;
        int tmp = 0;
        cntr.push_back(0);
        for (int i = 1; i <= n; i++)
        {
            tmp = 0;
            for (int j = 1; j <= n; j++)
            {
                if (v[cnt] <= 0)
                {
                    cout << "0 ";
                }
                else
                {
                    cout << "1 ";
                    tmp++;
                }
                cnt++;
            }
            cntr.push_back(tmp);
            cout << "\n";
        }

        // for(int i = n*n+1;i<=3867;i++){
        //     cin >> v[i];
        // }
        // int id = 978;
        // for(int i=0;i<17;i++){
        //     for(int j=1;j<18;j++){
        //         for(int k = 0;k<=j;k++){
        //             cout << v[id++] << " ";
        //         }
        //         cout << "\n";
        //     }
        //     cout << "\n";
        // }

        vector<int> nodes;
        for (int i1 = 1; i1 <= n; i1++)
        {
            nodes.push_back(i1);
            for (int i2 = i1 + 1; i2 <= n; i2++)
            {
                nodes.push_back(i2);
                for (int i3 = i2 + 1; i3 <= n; i3++)
                {
                    nodes.push_back(i3);
                    for (int i4 = i3 + 1; i4 <= n; i4++)
                    {
                        nodes.push_back(i4);
                        for (int i5 = i4 + 1; i5 <= n; i5++)
                        {
                            nodes.push_back(i5);
                            if (!checkNeg(nodes, 0, nc2(5) - 1))
                            {
                                for (int i = 0; i < nodes.size(); i++)
                                {
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
        for (int i1 = 1; i1 <= n; i1++)
        {
            nodes.push_back(i1);
            for (int i2 = i1 + 1; i2 <= n; i2++)
            {
                nodes.push_back(i2);
                for (int i3 = i2 + 1; i3 <= n; i3++)
                {
                    nodes.push_back(i3);
                    for (int i4 = i3 + 1; i4 <= n; i4++)
                    {
                        nodes.push_back(i4);
                        if (!checkPos(nodes, 0, nc2(4) - 2))
                        {
                            for (int i = 0; i < nodes.size(); i++)
                            {
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
        for (int i = 1; i < cntr.size(); i++)
        {
            cout << cntr[i] << " ";
        }
        cout << "\n";
        cout << "okok!\n";
        int ref1, ref2;
        ref1 = ref2 = 0;
        for (int k = 1; k <= n; k++)
        {
            if (v[flat(1, k)] <= 0 && v[flat(2, k)] >= 1)
                ref1++;
            if (v[flat(1, k)] >= 1 && v[flat(2, k)] >= 1)
                ref2++;
        }
        // cout << ref1 << " " << ref2 << "\n";
        // cout << "oop\n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    continue;
                // cout << "i, j\n";
                // cout << i << " " << j << "\n";
                int cnt1, cnt2;
                cnt1 = cnt2 = 0;
                for (int k = 1; k <= n; k++)
                {
                    // cout << v[flat(i, k)] << " " << v[flat(j, k)]<< "\n";
                    if (v[flat(i, k)] < 0 && v[flat(j, k)] >= 1)
                        cnt1++;
                    if (v[flat(i, k)] >= 1 && v[flat(j, k)] >= 1)
                        cnt2++;
                }
                // cout << cnt1 << " " << cnt2 << "\n";
                if(!(cntr[i] > cntr[1] || (cnt1 > ref1) || (cnt1 == ref1 && cnt2 >= ref2))){ cout << i << " " << j << "\n"; return 0;}
            }
        }
    }
}