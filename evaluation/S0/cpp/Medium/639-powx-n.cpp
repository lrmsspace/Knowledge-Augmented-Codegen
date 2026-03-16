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
public:
    double myPow(double x, int n) {
        if (n == 0) return 1.0;
        if (n < 0) {
            x = 1 / x;
            // Handle the case when n is INT_MIN
            if (n == INT_MIN) {
                n = INT_MAX;
                x = x * x; // Adjust for the extra multiplication
            } else {
                n = -n;
            }
        }

        double result = 1.0;
        double current_product = x;

        while (n > 0) {
            if (n % 2 == 1) {
                result *= current_product;
            }
            current_product *= current_product;
            n /= 2;
        }

        return result;          
    }
};
