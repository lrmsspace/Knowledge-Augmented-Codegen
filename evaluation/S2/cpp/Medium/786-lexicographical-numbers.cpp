// Source: https://leetcode.com/problems/lexicographical-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
//
// You must write an algorithm that runs in O(n) time and uses O(1) extra space.
//
// Example:
// Input: n = 13
// Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
//
// Constraints:
// 1 <= n <= 5 * 104
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
    vector<int> lexicalOrder(int n) {
        vector<int> result;
        int current = 1;

        for (int i = 0; i < n; ++i) {
            result.push_back(current);

            if (current * 10 <= n) {
                current *= 10;
            } else {
                while (current % 10 == 9 || current + 1 > n) {
                    current /= 10;
                }
                ++current;
            }
        }

        return result;          
    }
};
