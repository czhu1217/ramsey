# Unary Adder
This document tries to explain how the unary adder is incorporated into the program. 
The source code for k=1, 2, 3 can be found in `k1.cpp`, `k2.cpp`, and `k3.cpp` respectively. 
## Unary Adder for k=1
below is an example of a unary adder that counts the number of 1s in a given vector. 

It uses nC2 auxillary variables where n is the length of the given vector 

Example of rough idea: 

given `[0 1 0 1 1]`, the adder looks like
```
0
1 0
1 0 0
1 1 0 0
1 1 1 0 0 //this is the final result that signals there are 3 1s in the vector
```
```cpp
/*
@brief : counts the number of 1s in a vector with a unary counter
@param : a : a vector that is a row of the adj matrix
         start: the starting index to allocate auxilary variables
@return : returns the index of the next available variable
*/
int k1(vector<int> a, int start){
    int l = a.size();
    //pre: partial sum up to the previous index (used to calculate current partial sum)
    //cur: current partial sum
    //both have the form 111..100..0 where the # of 1s represents correspond to the number of ones up to the current index
    //can also be seen as a sorted row
    vector<int> pre, cur;

    //current var corresponding to whether the first index is a 1
    iff(start, a[0]);

    //push the partial sum up to first index into pre (with offset to avoid using index 0 of pre)
    pre.push_back(-1);
    pre.push_back(start++);

    //compute the partial sum up to index i of a
    for(int i = 1; i< a.size(); i++){
        cur.clear();
        cur.push_back(-1);

        //current partial sum is 0 if previous sum is 0 and a[i] is 0. 
        //cur[1] <-> pre[1] or a[i]
        print2(-pre[1], start);
        print2(-a[i], start);
        print3(-start, pre[1], a[i]);
        cur.push_back(start++);
        
        //loop all the possible 1 count: 1 to i
        for(int j=2;j<=i;j++){
            //the jth bit of current partial sum is 1 if it was 1 previously or it was 1 in the j-1th bit and a[i] is 1
            //cur[j] <-> pre[j] or (pre[j-1] and a[i])
            int b = a[i], c = pre[j], d = pre[j-1];
            print2(-c, start);
            print3(-b, -d, start);
            print3(b, c, -start);
            print3(d, c, -start);
            cur.push_back(start++);
        }
        //cur[i+1] <-> pre[i] and a[i]
        print2(-start, pre[i]);
        print2(-start, a[i]);
        print3(start, -pre[i], -a[i]);
        cur.push_back(start++);

        //set pre to cur for the iteration
        pre = cur;
        assert(pre.size()==i+2);
    }
    //returns the index of the next available index
    return start;
}
```
To get the final vector that represents the unary counter, we can take the indices from k1(a, start) - n to k1(a, start) - 1

## Unary adder for k=2 and k=3
The idea for k=2 and k=3 is very similar to k=1, except each of the unary adders look for something different than whether the current index of the given vector is a 1. 

### Condition to ensure k = 2
For k=2, we take in two vectors a and b,  and use the unary adder twice. 
- First we use the unary adder to count the number of (0, 1) pairs in the given pair of vectors. A (0, 1) pair is an index such that `a[i] = 0` and `b[i]=1`
- Then we counter the number of (1, 1) pairs similar to above
- We take the final vectors that represents each of the counters in the 2 steps above and concatenate them after the k=1 counter to get a vector of size 3n. 
- Lastly we compare this vector with the vector produces by the top two rows and makes sure that the vector produced by top two rows is always lexicographically smaller or equal to the current vector. 
```cpp
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
```

### Condition to ensure k=3
Similar to k=2, but instead of checking (0, 1) and (1, 1), it checks (0, 0, 1), (0, 1, 1), (1, 0, 1), (1, 1, 1). 