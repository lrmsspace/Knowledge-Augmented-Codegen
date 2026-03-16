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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String largestPalindrome(int n, int k) {
        // The largest n-digit palindrome can be constructed by taking the first half of the digits and mirroring them.
        // For odd n, we can include the middle digit in the first half.
        int halfLength = (n + 1) / 2;
        StringBuilder half = new StringBuilder();

        // Start with the largest possible half (all 9's).
        for (int i = 0; i < halfLength; i++) {
            half.append('9');
        }

        while (true) {
            String palindrome = createPalindrome(half.toString(), n % 2 == 1);
            if (palindrome.charAt(0) != '0' && Long.parseLong(palindrome) % k == 0) {
                return palindrome;
            }
            // Decrease the half and try again.
            long halfNum = Long.parseLong(half.toString());
            if (halfNum == 0) {
                break; // No more palindromes to check.
            }
            halfNum--;
            half = new StringBuilder(String.valueOf(halfNum));
        }

        return ""; // No valid palindrome found.            
    }
}
