// Source: https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return true if s is a good string, or false otherwise.
//
// A string s is good if all the characters that appear in s have the same number of occurrences (i.e., the same frequency).
//
// Example:
// Input: s = "abacbc"
// Output: true
// Explanation: The characters that appear in s are 'a', 'b', and 'c'. All characters occur 2 times in s.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//

class Solution {
    public boolean areOccurrencesEqual(String s) {
        int[] charCount = new int[26];
        for (char c : s.toCharArray()) {
            charCount[c - 'a']++;
        }

        int frequency = -1;
        for (int count : charCount) {
            if (count == 0) {
                continue;
            }
            if (frequency == -1) {
                frequency = count;
            } else if (frequency != count) {
                return false;
            }
        }
        return true;            
    }
}
