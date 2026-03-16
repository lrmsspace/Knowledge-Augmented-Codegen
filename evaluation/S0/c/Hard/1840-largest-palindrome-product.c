// Source: https://leetcode.com/problems/largest-palindrome-product/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
//
// Example:
// Input: n = 2
// Output: 987
// Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
//
// Constraints:
// 1 <= n <= 8
//

int largestPalindrome(int n) {
    if (n == 1) return 9;
    long long upper = 1;
    for (int i = 0; i < n; i++) upper *= 10;
    upper--;
    long long lower = upper / 10 + 1;
    for (long long firstHalf = upper; firstHalf >= lower; firstHalf--) {
        long long palin = firstHalf;
        long long rev = firstHalf;
        while (rev > 0) {
            palin = palin * 10 + (rev % 10);
            rev /= 10;
        }
        for (long long i = upper; i * i >= palin; i--) {
            if (palin % i == 0) {
                return (int)(palin % 1337);
            }
        }
    }
    return -1;      
}
