// Source: https://leetcode.com/problems/minimum-number-of-operations-to-reinitialize-a-permutation/   |   Difficulty: Medium
//
// Problem Description:
// You are given an even integer n​​​​​​. You initially have a permutation perm of size n​​ where perm[i] == i​ (0-indexed)​​​​.
//
// In one operation, you will create a new array arr, and for each i:
//
//
// 	If i % 2 == 0, then arr[i] = perm[i / 2].
// 	If i % 2 == 1, then arr[i] = perm[n / 2 + (i - 1) / 2].
//
//
// You will then assign arr​​​​ to perm.
//
// Return the minimum non-zero number of operations you need to perform on perm to return the permutation to its initial value.
//
// Example:
// Input: n = 2
// Output: 1
// Explanation: perm = [0,1] initially.
// After the 1st operation, perm = [0,1]
// So it takes only 1 operation.
//
// Constraints:
// 2 <= n <= 1000
// 	n​​​​​​ is even.
//

class Solution {
public:
    int reinitializePermutation(int n) {
        vector<int> perm(n);
        for (int i = 0; i < n; ++i) {
            perm[i] = i;
        }

        vector<int> original = perm;
        int operations = 0;

        do {
            vector<int> arr(n);
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) {
                    arr[i] = perm[i / 2];
                } else {
                    arr[i] = perm[n / 2 + (i - 1) / 2];
                }
            }
            perm = arr;
            operations++;
        } while (perm != original);

        return operations;          
    }
};
