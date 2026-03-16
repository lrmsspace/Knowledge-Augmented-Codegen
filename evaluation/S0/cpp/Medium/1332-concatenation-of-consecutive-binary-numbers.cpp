// Source: https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 1
// Explanation: "1" in binary corresponds to the decimal value 1.
//
// Constraints:
// 1 <= n <= 105
//

class Solution {
public:
    int concatenatedBinary(int n) {
        const int MOD = 1e9 + 7;
        long long result = 0;
        int length = 0;

        for (int i = 1; i <= n; ++i) {
            if ((i & (i - 1)) == 0) { // Check if i is a power of two
                ++length;
            }
            result = ((result << length) | i) % MOD;
        }

        return static_cast<int>(result);            
    }
};
