// Source: https://leetcode.com/problems/minimum-deletions-for-at-most-k-distinct-characters/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting of lowercase English letters, and an integer k.
//
// Your task is to delete some (possibly none) of the characters in the string so that the number of distinct characters in the resulting string is at most k.
//
// Return the minimum number of deletions required to achieve this.
//
// Example:
// Input: s = "abc", k = 2
//
// Output: 1
//
// Explanation:
//
//
// 	s has three distinct characters: 'a', 'b' and 'c', each with a frequency of 1.
// 	Since we can have at most k = 2 distinct characters, remove all occurrences of any one character from the string.
// 	For example, removing all occurrences of 'c' results in at most k distinct characters. Thus, the answer is 1.
//
// Constraints:
// 1 <= s.length <= 16
// 	1 <= k <= 16
// 	s consists only of lowercase English letters.
//

class Solution {
    public int minDeletion(String s, int k) {
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        Arrays.sort(freq);

        int deletions = 0;
        int distinctCount = 0;

        for (int i = 25; i >= 0; i--) {
            if (freq[i] > 0) {
                distinctCount++;
                if (distinctCount > k) {
                    deletions += freq[i];
                }
            }
        }

        return deletions;           
    }
}
