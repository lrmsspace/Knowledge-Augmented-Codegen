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

int nthMagicalNumber(int n, int a, int b) {
    const int MOD = 1000000007;

    long long lcm_ab = (long long)a / __gcd(a, b) * b;
    long long left = 1, right = (long long)n * (a < b ? a : b);
    while (left < right) {
        long long mid = left + (right - left) / 2;
        long long count = mid / a + mid / b - mid / lcm_ab;
        if (count < n) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return (int)(left % MOD);       
}
