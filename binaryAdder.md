# Binary Adder
Most of the implementation below are based on the binary adder descibed in [this paper](http://www.diva-portal.org/smash/get/diva2:721407/FULLTEXT01.pdf)
## Half Adder
The half adder deals with the least significant digit where there's only two inputs and no carry

![half adder](https://i.imgur.com/NnRI467.png)



```cpp
/*
    Input: takes in two digits a, b and st, a starting index to write auxillary variables
    Output: returns {s, c} : {resulting current digit in the sum, carry}
*/
pi halfAdder(int a, int b, int st){
    int s = st;
    //s <-> a xor b
    //s <-> (-a and b) or (a and -b)
    /*cnf form: 
        (A ∨ ¬B ∨ S) ∧ (¬A ∨ B ∨ S) ∧ (¬B ∨ ¬A ∨ ¬S) ∧ (A ∨ B ∨ ¬S)
    */

    print3(a, -b, s);
    print3(-a, b, s);
    print3(-b, -a, -s);
    print3(a, b, -s);
    st++;

    int c = st;
    //c <-> a and b
    print3(-a, -b, c);
    print2(-c, a);
    print2(-c, b);

    return {s, c};

}
```
## Full Adder
The full adder is used to calculate subsequent digit additons where there may be carry from previous calculations.

![Full adder](https://i.imgur.com/G8NawT6.png)

```cpp

/*
    Input: 
        a, b: 2 binary digits
        c: carry from previous calculation
        st: starting index to write auxillary variables
    Output: returns {s, co} : {resulting current digit in the sum, carry}
*/
pi fullAdder(int a, int b, int c, int st){
    int s = st;
    //st (s) <-> a xor b xor c
    /*cnf form:
        (B ∨ A ∨ ¬C ∨ St) ∧ (¬C ∨ A ∨ B ∨ St) ∧ (B ∨ ¬C ∨ A ∨ St) ∧ (¬C ∨ ¬A ∨ ¬B ∨ St)
        ∧ (B ∨ C ∨ ¬A ∨ St) ∧ (B ∨ ¬A ∨ C ∨ St) ∧ (A ∨ C ∨ ¬B ∨ St) ∧ (¬St ∨ ¬A ∨ C ∨ ¬B)
        ∧ (¬St ∨ ¬B ∨ C ∨ ¬A) ∧ (¬St ∨ ¬B ∨ A ∨ ¬C) ∧ (¬St ∨ ¬A ∨ B ∨ ¬C) ∧ (¬St ∨ C ∨ A ∨ B)
    */
    print4(b, a, -c, st); print4(-c, a, b, st); print4(b, -c, a, st); print4(-c, -a, -b, st);
    print4(b, c, -a, st); print4(b, -a, c, st); print4(a, c, -b, st); print4(-st, -a, c, -b);
    print4(-st, -b, c, -a); print4(-st, -b, a, -c); print4(-st, -a, b, -c); print4(-st, c, a, b);
    st++;
    int co = st;
    //st (co) <-> (a or b) and (a or c) and (b or c)
    //(¬A ∨ ¬B ∨ St) ∧ (¬C ∨ ¬A ∨ ¬B ∨ St) ∧ (¬C ∨ ¬B ∨ St) ∧ (¬A ∨ ¬C ∨ St)
    //(¬A ∨ ¬B ∨ ¬C ∨ St) ∧ (¬St ∨ A ∨ B) ∧ (¬St ∨ A ∨ C) ∧ (¬St ∨ B ∨ C)
    print3(-a, -b, st); print4(-c, -a, -b, st); print3(-c, -b, st); print3(-a, -c, st);
    print4(-a, -b, -c, st); print3(-st, a, b); print3(-st, a, c); print3(-st, b, c);
    return {s, co};
}
```
## The Ripple Adder
The ripple adder utilizes half adder and full adder to add two inputs of the same length

![ripple adder](https://i.imgur.com/ZPvSxYq.png)

```cpp

//input: Two non-negative i-bit numbers a and b (stored as vectors of the same length), least significant bit first
//output:  an n i + 1-bit non-negative number (stored in a vector) which is the sum of a and b, least significant bit first.
vi rippleAdder(vi a, vi b, int &st){
    assert(a.size()==b.size());
    int l = a.size();
    vi ans;

    //compute the least sig bit
    pi p = halfAdder(a[0], b[0], st);
    st += 2;
    //store least sig bit into answer vector 
    ans.pb(p.f);

    //computer the 2nd to second last digit
    FOR(i, 1, l-1){
        //compute current (digit, carry) pair
        p = fullAdder(a[i], b[i], p.s, st);
        st += 2;
        //store current digit into answer
        ans.pb(p.f);
    }
    //store last carry into answer
    ans.pb(p.s);
    return ans;
}
```



## k=1 using the ripple adder

```cpp

//zero is a variable that's always set to false, one is a variable that's always set to true
int zero, one;
/*
	input: a vector representing a row of adj matrix and the starting index to write variables
	output: a vector representing the binary counter, least significant diigt first
*/
vi k1(vector<int> a, int &start){
    //ans will be used as the accumulated sum
    vi ans;
    //initially ans is 0
    ans.pb(zero); 

    //compute the sum by adding each digit with the accumulated sum
    FOR(i, 0, a.size()-1){
        vi cur;
        //len is the maximum possible length of ans up to this point
        int len = log2(i+1)+1;

        //make cur the same length as ans by adding a[i] to the front and leading zeros afterwards
        cur.pb(a[i]); 
        while(cur.size()<len) cur.pb(zero);

        //prune ans if it's longer than len (getting rid of most sig digit since we know it must be 0)
        while(ans.size()>len){
            int z = ans.back();
            ans.pop_back();
        }

        //compute new accumulated sum by passing in current sum, digit, starting index of new var to rippleAdder
        ans = rippleAdder(ans, cur, start);
    }

    return ans;
}
```

