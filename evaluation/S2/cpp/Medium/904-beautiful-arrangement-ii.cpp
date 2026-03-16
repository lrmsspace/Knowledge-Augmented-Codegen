// Source: https://leetcode.com/problems/beautiful-arrangement-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, construct a list answer that contains n different positive integers ranging from 1 to n and obeys the following requirement:
//
//
// 	Suppose this list is answer = [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.
//
//
// Return the list answer. If there multiple valid answers, return any of them.
//
// Example:
// Input: n = 3, k = 1
// Output: [1,2,3]
// Explanation: The [1,2,3] has three different positive integers ranging from 1 to 3, and the [1,1] has exactly 1 distinct integer: 1
//
// Constraints:
// 1 <= k < n <= 104
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
    vector<int> constructArray(int n, int k) {
        vector<int> answer(n);
        for (int i = 0; i < n - k - 1; ++i) {
            answer[i] = i + 1;
        }
        for (int i = n - k - 1; i < n; ++i) {
            if ((i - n + k + 1) % 2 == 0) {
                answer[i] = n - (i - n + k + 1) / 2;
            } else {
                answer[i] = n - k + (i - n + k + 1) / 2;
            }
        }
        return answer;          
    }
};
