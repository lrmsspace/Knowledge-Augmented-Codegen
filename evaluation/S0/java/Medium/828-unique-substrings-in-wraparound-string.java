// Source: https://leetcode.com/problems/unique-substrings-in-wraparound-string/   |   Difficulty: Medium
//
// Problem Description:
// We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
//
//
// 	"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
//
//
// Given a string s, return the number of unique non-empty substrings of s are present in base.
//
// Example:
// Input: s = "a"
// Output: 1
// Explanation: Only the substring "a" of s is in base.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//

class Solution {
    public int findSubstringInWraproundString(String s) {
        int[] count = new int[26];
        int maxLengthCur = 0;

        for (int i = 0; i < s.length(); i++) {
            if (i > 0 && (s.charAt(i) - s.charAt(i - 1) + 26) % 26 == 1) {
                maxLengthCur++;
            } else {
                maxLengthCur = 1;
            }
            int index = s.charAt(i) - 'a';
            count[index] = Math.max(count[index], maxLengthCur);
        }

        int result = 0;
        for (int c : count) {
            result += c;
        }
        return result;          
    }
}
