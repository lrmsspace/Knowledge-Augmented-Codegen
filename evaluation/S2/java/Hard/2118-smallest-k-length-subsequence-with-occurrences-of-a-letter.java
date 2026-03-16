// Source: https://leetcode.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s, an integer k, a letter letter, and an integer repetition.
//
// Return the lexicographically smallest subsequence of s of length k that has the letter letter appear at least repetition times. The test cases are generated so that the letter appears in s at least repetition times.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// A string a is lexicographically smaller than a string b if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
//
// Example:
// Input: s = "leet", k = 3, letter = "e", repetition = 1
// Output: "eet"
// Explanation: There are four subsequences of length 3 that have the letter 'e' appear at least 1 time:
// - "lee" (from "leet")
// - "let" (from "leet")
// - "let" (from "leet")
// - "eet" (from "leet")
// The lexicographically smallest subsequence among them is "eet".
//
// Constraints:
// 1 <= repetition <= k <= s.length <= 5 * 104
// 	s consists of lowercase English letters.
// 	letter is a lowercase English letter, and appears in s at least repetition times.
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
    public String smallestSubsequence(String s, int k, char letter, int repetition) {
        int n = s.length();
        int countLetter = 0;
        for (char c : s.toCharArray()) {
            if (c == letter) {
                countLetter++;
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            while (sb.length() > 0 && sb.charAt(sb.length() - 1) > c
                    && sb.length() + (n - i) > k
                    && (sb.charAt(sb.length() - 1) != letter || countLetter > repetition)) {
                if (sb.charAt(sb.length() - 1) == letter) {
                    repetition++;
                }
                sb.deleteCharAt(sb.length() - 1);
            }

            if (sb.length() < k) {
                sb.append(c);
                if (c == letter) {
                    repetition--;
                }
            }

            if (c == letter) {
                countLetter--;
            }
        }

        return sb.toString();           
    }
}
