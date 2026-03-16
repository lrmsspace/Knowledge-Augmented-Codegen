// Source: https://leetcode.com/problems/rearrange-k-substrings-to-form-target-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t, both of which are anagrams of each other, and an integer k.
//
// Your task is to determine whether it is possible to split the string s into k equal-sized substrings, rearrange the substrings, and concatenate them in any order to create a new string that matches the given string t.
//
// Return true if this is possible, otherwise, return false.
//
// An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, using all the original letters exactly once.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "abcd", t = "cdab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	Split s into 2 substrings of length 2: ["ab", "cd"].
// 	Rearranging these substrings as ["cd", "ab"], and then concatenating them results in "cdab", which matches t.
//
// Constraints:
// 1 <= s.length == t.length <= 2 * 105
// 	1 <= k <= s.length
// 	s.length is divisible by k.
// 	s and t consist only of lowercase English letters.
// 	The input is generated such that s and t are anagrams of each other.
//

class Solution {
    public boolean isPossibleToRearrange(String s, String t, int k) {
        int n = s.length();
        if (n % k != 0) {
            return false;
        }

        int substringLength = n / k;
        int[] freqS = new int[26];
        int[] freqT = new int[26];

        for (int i = 0; i < n; i++) {
            freqS[s.charAt(i) - 'a']++;
            freqT[t.charAt(i) - 'a']++;
        }

        for (int i = 0; i < 26; i++) {
            if (freqS[i] != freqT[i]) {
                return false;
            }
        }

        return true;            
    }
}
