// Source: https://leetcode.com/problems/smallest-value-after-replacing-with-sum-of-prime-factors/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n.
//
// Continuously replace n with the sum of its prime factors.
//
//
// 	Note that if a prime factor divides n multiple times, it should be included in the sum as many times as it divides n.
//
//
// Return the smallest value n will take on.
//
// Example:
// Input: n = 15
// Output: 5
// Explanation: Initially, n = 15.
// 15 = 3 * 5, so replace n with 3 + 5 = 8.
// 8 = 2 * 2 * 2, so replace n with 2 + 2 + 2 = 6.
// 6 = 2 * 3, so replace n with 2 + 3 = 5.
// 5 is the smallest value n will take on.
//
// Constraints:
// 2 <= n <= 105
//

class Solution {
public:
    int smallestValue(int n) {
        auto sumOfPrimeFactors = [](int num) {
            int sum = 0;
            for (int i = 2; i * i <= num; ++i) {
                while (num % i == 0) {
                    sum += i;
                    num /= i;
                }
            }
            if (num > 1) {
                sum += num;
            }
            return sum;
        };

        int prev = -1;
        while (n != prev) {
            prev = n;
            n = sumOfPrimeFactors(n);
        }
        return n;           
    }
};
