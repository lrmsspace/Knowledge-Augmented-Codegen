// Source: https://leetcode.com/problems/powx-n/   |   Difficulty: Medium
//
// Problem Description:
// Implement pow(x, n), which calculates x raised to the power n (i.e., xn).
//
// Example:
// Input: x = 2.00000, n = 10
// Output: 1024.00000
//
// Constraints:
// -100.0 < x < 100.0
// 	-231 <= n <= 231-1
// 	n is an integer.
// 	Either x is not zero or n > 0.
// 	-104 <= xn <= 104
//

class Solution {
    public double myPow(double x, int n) {
        if (n == 0) {
            return 1.0;
        }
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }
        double half = myPow(x, n / 2);
        if (n % 2 == 0) {
            return half * half;
        } else {
            return half * half * x;
        }           
    }
}
