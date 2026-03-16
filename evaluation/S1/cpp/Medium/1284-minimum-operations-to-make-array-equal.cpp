// Source: https://leetcode.com/problems/minimum-operations-to-make-array-equal/   |   Difficulty: Medium
//
// Problem Description:
// You have an array arr of length n where arr[i] = (2 * i) + 1 for all valid values of i (i.e., 0 <= i < n).
//
// In one operation, you can select two indices x and y where 0 <= x, y < n and subtract 1 from arr[x] and add 1 to arr[y] (i.e., perform arr[x] -=1 and arr[y] += 1). The goal is to make all the elements of the array equal. It is guaranteed that all the elements of the array can be made equal using some operations.
//
// Given an integer n, the length of the array, return the minimum number of operations needed to make all the elements of arr equal.
//
// Example:
// Input: n = 3
// Output: 2
// Explanation: arr = [1, 3, 5]
// First operation choose x = 2 and y = 0, this leads arr to be [2, 3, 4]
// In the second operation choose x = 2 and y = 0 again, thus arr = [3, 3, 3].
//
// Constraints:
// 1 <= n <= 104
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(int n) {
        // The array is [1, 3, 5, ..., (2n - 1)]
        // The target value for all elements is n (the average)
        // The number of operations needed is the sum of differences
        // between elements less than n and n itself.
        int ops = 0;
        for (int i = 0; i < n / 2; ++i) {
            ops += (n - (2 * i + 1));
        }
        return ops;         
    }
};
