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

int consecutiveNumbersSum(int n) {
    int count = 0;
    for (long long k = 1; k * (k + 1) / 2 <= n; k++) {
        if ((n - k * (k - 1) / 2) % k == 0) {
            count++;
        }
    }
    return count;       
}
