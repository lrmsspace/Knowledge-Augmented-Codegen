// Source: https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, you need to partition it into one or more balanced substrings. For example, if s == "ababcc" then ("abab", "c", "c"), ("ab", "abc", "c"), and ("ababcc") are all valid partitions, but ("a", "bab", "cc"), ("aba", "bc", "c"), and ("ab", "abcc") are not. The unbalanced substrings are bolded.
//
// Return the minimum number of substrings that you can partition s into.
//
// Note: A balanced string is a string where each character in the string occurs the same number of times.
//
// Example:
// Input: s = "fabccddg"
//
// Output: 3
//
// Explanation:
//
// We can partition the string s into 3 substrings in one of the following ways: ("fab, "ccdd", "g"), or ("fabc", "cd", "dg").
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists only of English lowercase letters.
//

class Solution {
    public int minimumSubstringsInPartition(String s) {
        int count = 0;
        int i = 0;
        int n = s.length();

        while (i < n) {
            int[] freq = new int[26];
            int maxFreq = 0;
            int distinctChars = 0;

            for (int j = i; j < n; j++) {
                char ch = s.charAt(j);
                freq[ch - 'a']++;

                if (freq[ch - 'a'] == 1) {
                    distinctChars++;
                }

                maxFreq = Math.max(maxFreq, freq[ch - 'a']);

                boolean isBalanced = true;
                for (int k = 0; k < 26; k++) {
                    if (freq[k] != 0 && freq[k] != maxFreq) {
                        isBalanced = false;
                        break;
                    }
                }

                if (isBalanced) {
                    count++;
                    i = j + 1;
                    break;
                }

                if (j == n - 1) {
                    // If we reach the end without finding a balanced substring,
                    // we need to move to the next character.
                    i++;
                }
            }
        }

        return count;           
    }
}
