// Source: https://leetcode.com/problems/find-the-largest-palindrome-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// Return the largest integer having n digits (as a string) that is k-palindromic.
//
// Note that the integer must not have leading zeros.
//
// Example:
// Input: n = 3, k = 5
//
// Output: "595"
//
// Explanation:
//
// 595 is the largest k-palindromic integer with 3 digits.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= k <= 9
//

class Solution {
    public String largestPalindrome(int n, int k) {
        if (n == 1) {
            for (int i = 9; i >= 1; i--) {
                if (i % k == 0) {
                    return String.valueOf(i);
                }
            }
            return "";
        }

        StringBuilder half = new StringBuilder();
        half.append('9');
        for (int i = 1; i < (n + 1) / 2; i++) {
            half.append('9');
        }

        long halfNum = Long.parseLong(half.toString());

        while (halfNum >= Math.pow(10, (n - 1) / 2)) {
            StringBuilder palin = new StringBuilder(half.toString());
            String rev = new StringBuilder(half.toString()).reverse().toString();
            if (n % 2 == 1) {
                palin.append(rev.substring(1));
            } else {
                palin.append(rev);
            }

            long palinNum = Long.parseLong(palin.toString());
            if (palinNum % k == 0) {
                return palin.toString();
            }

            halfNum--;
            half = new StringBuilder(String.valueOf(halfNum));
        }

        return "";          
    }
}
