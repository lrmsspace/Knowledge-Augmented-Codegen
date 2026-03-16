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

class Solution {
    public int largestPalindrome(int n) {
        if (n == 1) return 9;

        int upperLimit = (int) Math.pow(10, n) - 1;
        int lowerLimit = (int) Math.pow(10, n - 1);

        for (int firstHalf = upperLimit; firstHalf >= lowerLimit; firstHalf--) {
            long palindrome = createPalindrome(firstHalf);
            for (long i = upperLimit; i * i >= palindrome; i--) {
                if (palindrome % i == 0) {
                    long otherFactor = palindrome / i;
                    if (otherFactor >= lowerLimit && otherFactor <= upperLimit) {
                        return (int) (palindrome % 1337);
                    }
                }
            }
        }
        return -1;          
    }
}
