// Source: https://leetcode.com/problems/find-longest-awesome-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it a palindrome.
//
// Return the length of the maximum length awesome substring of s.
//
// Example:
// Input: s = "3242415"
// Output: 5
// Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of digits.
//

class Solution {
    public int longestAwesome(String s) {
        int n = s.length();
        int[] pos = new int[1024];
        for (int i = 0; i < 1024; i++) {
            pos[i] = -1;
        }
        pos[0] = 0;

        int mask = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            int digit = s.charAt(i) - '0';
            mask ^= (1 << digit);

            if (pos[mask] >= 0) {
                maxLen = Math.max(maxLen, i + 1 - pos[mask]);
            } else {
                pos[mask] = i + 1;
            }

            for (int j = 0; j < 10; j++) {
                int toggledMask = mask ^ (1 << j);
                if (pos[toggledMask] >= 0) {
                    maxLen = Math.max(maxLen, i + 1 - pos[toggledMask]);
                }
            }
        }

        return maxLen;                  
    }
}
