// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a palindromic string s and an integer k.
//
// Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
//
// Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
//
// Example:
// Input: s = "abba", k = 2
//
// Output: "baab"
//
// Explanation:
//
//
// 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
// 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
// 	1 <= k <= 106
//

class Solution {
    public String smallestPalindrome(String s, int k) {
        int n = s.length();
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }

        StringBuilder half = new StringBuilder();
        char mid = 0;
        for (int i = 0; i < 26; i++) {
            if (count[i] % 2 == 1) {
                mid = (char) (i + 'a');
            }
            for (int j = 0; j < count[i] / 2; j++) {
                half.append((char) (i + 'a'));
            }
        }

        String halfStr = half.toString();
        StringBuilder result = new StringBuilder();
        if (!findKthPermutation(halfStr.toCharArray(), k, result)) {
            return "";
        }

        String firstHalf = result.toString();
        String secondHalf = new StringBuilder(firstHalf).reverse().toString();
        return firstHalf + (mid == 0 ? "" : mid) + secondHalf;          
    }
}
