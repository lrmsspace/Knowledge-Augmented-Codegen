// Source: https://leetcode.com/problems/three-divisors/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if n has exactly three positive divisors. Otherwise, return false.
//
// An integer m is a divisor of n if there exists an integer k such that n = k * m.
//
// Example:
// Input: n = 2
// Output: false
// Explantion: 2 has only two divisors: 1 and 2.
//
// Constraints:
// 1 <= n <= 104
//

class Solution {
public:
    bool isThree(int n) {
        if (n < 4) return false; // The smallest number with exactly three divisors is 4 (1, 2, 4)

        int sqrt_n = static_cast<int>(sqrt(n));
        if (sqrt_n * sqrt_n != n) return false; // n must be a perfect square

        // Check if sqrt_n is prime
        for (int i = 2; i * i <= sqrt_n; ++i) {
            if (sqrt_n % i == 0) {
                return false; // Found a divisor, so sqrt_n is not prime
            }
        }
        return true; // sqrt_n is prime, so n has exactly three divisors            
    }
};
