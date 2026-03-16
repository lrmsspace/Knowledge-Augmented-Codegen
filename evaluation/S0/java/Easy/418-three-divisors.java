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
    public boolean isThree(int n) {
        if (n < 4) {
            return false;
        }

        int sqrtN = (int) Math.sqrt(n);
        if (sqrtN * sqrtN != n) {
            return false;
        }

        for (int i = 2; i * i <= sqrtN; i++) {
            if (sqrtN % i == 0) {
                return false;
            }
        }

        return true;            
    }
}
