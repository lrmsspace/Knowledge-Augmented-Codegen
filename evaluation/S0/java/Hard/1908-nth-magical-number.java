// Source: https://leetcode.com/problems/nth-magical-number/   |   Difficulty: Hard
//
// Problem Description:
// A positive integer is magical if it is divisible by either a or b.
//
// Given the three integers n, a, and b, return the nth magical number. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 1, a = 2, b = 3
// Output: 2
//
// Constraints:
// 1 <= n <= 109
// 	2 <= a, b <= 4 * 104
//

class Solution {
    public int nthMagicalNumber(int n, int a, int b) {
        long left = 0, right = (long) 1e18;
        long mod = (long) 1e9 + 7;
        long lcm = lcm(a, b);

        while (left < right) {
            long mid = left + (right - left) / 2;
            long count = mid / a + mid / b - mid / lcm;

            if (count < n) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return (int) (left % mod);          
    }
}
