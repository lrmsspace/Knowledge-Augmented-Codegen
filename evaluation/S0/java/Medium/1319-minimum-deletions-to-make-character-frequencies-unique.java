// Source: https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/   |   Difficulty: Medium
//
// Problem Description:
// A string s is called good if there are no two different characters in s that have the same frequency.
//
// Given a string s, return the minimum number of characters you need to delete to make s good.
//
// The frequency of a character in a string is the number of times it appears in the string. For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
//
// Example:
// Input: s = "aab"
// Output: 0
// Explanation: s is already good.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

class Solution {
    public int minDeletions(String s) {
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        Set<Integer> usedFrequencies = new HashSet<>();
        int deletions = 0;

        for (int f : freq) {
            while (f > 0 && !usedFrequencies.add(f)) {
                f--;
                deletions++;
            }
        }

        return deletions;           
    }
}
