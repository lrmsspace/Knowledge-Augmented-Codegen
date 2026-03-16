// Source: https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers startPos and endPos. Initially, you are standing at position startPos on an infinite number line. With one step, you can move either one position to the left, or one position to the right.
//
// Given a positive integer k, return the number of different ways to reach the position endPos starting from startPos, such that you perform exactly k steps. Since the answer may be very large, return it modulo 109 + 7.
//
// Two ways are considered different if the order of the steps made is not exactly the same.
//
// Note that the number line includes negative integers.
//
// Example:
// Input: startPos = 1, endPos = 2, k = 3
// Output: 3
// Explanation: We can reach position 2 from 1 in exactly 3 steps in three ways:
// - 1 -> 2 -> 3 -> 2.
// - 1 -> 2 -> 1 -> 2.
// - 1 -> 0 -> 1 -> 2.
// It can be proven that no other way is possible, so we return 3.
//
// Constraints:
// 1 <= startPos, endPos, k <= 1000
//

class Solution {
public:
    int numberOfWays(int startPos, int endPos, int k) {
        const int MOD = 1e9 + 7;
        int distance = abs(endPos - startPos);
        
        // If the distance is greater than k or if the parity of (k - distance) is odd, return 0
        if (distance > k || (k - distance) % 2 != 0) {
            return 0;
        }

        int rightSteps = (k + distance) / 2;
        long long result = 1;

        // Calculate C(k, rightSteps) using multiplicative formula
        for (int i = 0; i < rightSteps; ++i) {
            result = result * (k - i) % MOD;
            result = result * modInverse(i + 1, MOD) % MOD;
        }

        return static_cast<int>(result);            
    }
};
