// Source: https://leetcode.com/problems/minimum-array-end/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and x. You have to construct an array of positive integers nums of size n where for every 0 <= i < n - 1, nums[i + 1] is greater than nums[i], and the result of the bitwise AND operation between all elements of nums is x.
//
// Return the minimum possible value of nums[n - 1].
//
// Example:
// Input: n = 3, x = 4
//
// Output: 6
//
// Explanation:
//
// nums can be [4,5,6] and its last element is 6.
//
// Constraints:
// 1 <= n, x <= 108
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
    long long minEnd(int n, int x) {
        long long ans = x;
        for (int i = 1; i < n; ++i) {
            ans |= (1LL << (63 - __builtin_clzll(ans)));
        }
        return ans;         
    }
};
