// { Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int getMid(int s, int e) {
    return s + (e - s) / 2;
}

ll constructSTUtil(int *arr, int ss, int se, ll *st, int si) {
    if (ss == se) {
        st[si] = arr[ss];
        return arr[ss];
    }
    int mid = getMid(ss, se);
    st[si] = constructSTUtil(arr, ss, mid, st, si * 2 + 1) +
             constructSTUtil(arr, mid + 1, se, st, si * 2 + 2);
    return st[si];
}

ll *constructST(int *arr, int n) {
    int x = (int)(ceil(log2(n)));
    int max_size = 2 * (int)pow(2, x) - 1;
    ll *st = new ll[max_size];
    constructSTUtil(arr, 0, n - 1, st, 0);
    return st;
}

ll getsum(ll *st, int n, int l, int r);
void updateValue(int *, ll *, int, int, int);


 // } Driver Code Ends
// User function template for C++

// arr : given array
// n : size of arr
// index : need to update
// new_val : given value to which we need to update index
// st : constructed segment-tree

//Function to update a value in input array and segment tree.
//recursive function to update the nodes which have given index in their range. 
void updateValueUtil(ll *st, int ss, int se, int i, int diff, int si) 
{
    //base case
    if (i < ss || i > se) 
    return;

    //if the input index is in range of this node then we update
    //the value of the node and its children. 
    st[si] = st[si] + diff;
    if (se != ss) {
        int mid = getMid(ss, se);
        updateValueUtil(st, ss, mid, i, diff, 2 * si + 1);
        updateValueUtil(st, mid + 1, se, i, diff, 2 * si + 2);
    }
}

//Function to update a value in input array and segment tree.
//It uses updateValueUtil() to update the value in segment tree.
void updateValue(int *arr, ll *st, int n, int index, int new_val)
{
    //base case for invalid input.
    if (index < 0 || index > n - 1) 
    {
        return;
    }
    
    //finding the difference between new value and old value
    //and updating the value in array.
    int diff = new_val - arr[index];
    arr[index] = new_val;
    

    //updating the value of nodes in segment tree.
    updateValueUtil(st, 0, n - 1, index, diff, 0);
}

//recursive function to get the sum of values in the given range of the array.
ll getSumUtil(ll *st, int ss, int se, int l, int r, int si) 
{
    //if segment of this node is a part of given range then we
    // return the sum of the segment.
    if (l <= ss && r >= se) 
    return st[si];
    
    //if segment of this node is outside the given range, we return 0.
    if (se < l || ss > r) 
    return 0;
    
    //if a part of this segment overlaps with the given range, we call
    //the function recursively for the children nodes.
    int mid = getMid(ss, se);
    return getSumUtil(st, ss, mid, l, r, 2 * si + 1) +
           getSumUtil(st, mid + 1, se, l, r, 2 * si + 2);
}


//Function to return sum of elements in range from index qs (query start)
//to qe (query end). It mainly uses getSumUtil().
ll getsum(ll *st, int n, int l, int r) 
{
    //base case for invalid input
    if (l < 0 || r > n - 1 || l > r) 
    {
        return -1;
    }

    return getSumUtil(st, 0, n - 1, l, r, 0);
}


// { Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int num, query;
        cin >> num >> query;
        int arr[num];
        for (int i = 0; i < num; i++) cin >> arr[i];

        ll *st = constructST(arr, num);
        int L, R, index, val;
        char type;
        while (query--) {
            cin.ignore(INT_MAX, '\n');
            cin >> type;
            if (type == 'G') {
                cin >> L >> R;
                cout << getsum(st, num, L, R) << endl;
            } else {
                cin >> index >> val;
                updateValue(arr, st, num, index, val);
            }
        }
    }

    return 0;
}
  // } Driver Code Ends