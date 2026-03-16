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

int reinitializePermutation(int n) {
    int count = 0;
    int pos = 1; // Start from index 1
    do {
        if (pos % 2 == 0) {
            pos = pos / 2;
        } else {
            pos = n / 2 + (pos - 1) / 2;
        }
        count++;
    } while (pos != 1);
    return count;       
}
