// Source: https://leetcode.com/problems/consecutive-numbers-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of ways you can write n as the sum of consecutive positive integers.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: 5 = 2 + 3
//
// Constraints:
// 1 <= n <= 109
//

class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int count = 0;
        for (long long k = 1; k * (k + 1) / 2 <= n; k++) {
            long long numerator = n - k * (k - 1) / 2;
            if (numerator % k == 0) {
                count++;
            }
        }
        return count;           
    }
};
