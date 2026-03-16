// Source: https://leetcode.com/problems/ugly-number-iii/   |   Difficulty: Medium
//
// Problem Description:
// An ugly number is a positive integer that is divisible by a, b, or c.
//
// Given four integers n, a, b, and c, return the nth ugly number.
//
// Example:
// Input: n = 3, a = 2, b = 3, c = 5
// Output: 4
// Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
//
// Constraints:
// 1 <= n, a, b, c <= 109
// 	1 <= a * b * c <= 1018
// 	It is guaranteed that the result will be in range [1, 2 * 109].
//

int nthUglyNumber(int n, int a, int b, int c) {
    long long left = 1, right = 2000000000, mid;
    long long ab = (long long)a * b / __gcd(a, b);
    long long ac = (long long)a * c / __gcd(a, c);
    long long bc = (long long)b * c / __gcd(b, c);
    long long abc = (long long)ab * c / __gcd(ab, c);

    while (left < right) {
        mid = left + (right - left) / 2;
        long long count = mid / a + mid / b + mid / c - mid / ab - mid / ac - mid / bc + mid / abc;

        if (count < n) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return (int)left;       
}
