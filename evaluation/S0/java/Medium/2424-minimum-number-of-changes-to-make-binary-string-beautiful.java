// Source: https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary string s having an even length.
//
// A string is beautiful if it's possible to partition it into one or more substrings such that:
//
//
// 	Each substring has an even length.
// 	Each substring contains only 1's or only 0's.
//
//
// You can change any character in s to 0 or 1.
//
// Return the minimum number of changes required to make the string s beautiful.
//
// Example:
// Input: s = "1001"
// Output: 2
// Explanation: We change s[1] to 1 and s[3] to 0 to get string "1100".
// It can be seen that the string "1100" is beautiful because we can partition it into "11|00".
// It can be proven that 2 is the minimum number of changes needed to make the string beautiful.
//
// Constraints:
// 2 <= s.length <= 105
// 	s has an even length.
// 	s[i] is either '0' or '1'.
//

class Solution {
    public int minChanges(String s) {
        int changesStartingWith0 = 0;
        int changesStartingWith1 = 0;

        for (int i = 0; i < s.length(); i++) {
            char expectedCharFor0 = (i % 2 == 0) ? '0' : '1';
            char expectedCharFor1 = (i % 2 == 0) ? '1' : '0';

            if (s.charAt(i) != expectedCharFor0) {
                changesStartingWith0++;
            }
            if (s.charAt(i) != expectedCharFor1) {
                changesStartingWith1++;
            }
        }

        return Math.min(changesStartingWith0, changesStartingWith1);            
    }
}
