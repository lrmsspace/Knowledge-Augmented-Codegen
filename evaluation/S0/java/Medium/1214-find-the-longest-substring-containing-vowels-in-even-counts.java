// Source: https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/   |   Difficulty: Medium
//
// Problem Description:
// Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
//
// Example:
// Input: s = "eleetminicoworoep"
// Output: 13
// Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
//
// Constraints:
// 1 <= s.length <= 5 x 10^5
// 	s contains only lowercase English letters.
//

class Solution {
    public int findTheLongestSubstring(String s) {
        int n = s.length();
        int[] pos = new int[32];
        for (int i = 0; i < 32; i++) {
            pos[i] = -1;
        }
        pos[0] = 0;

        int state = 0;
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            char ch = s.charAt(i);
            switch (ch) {
                case 'a':
                    state ^= 1 << 0;
                    break;
                case 'e':
                    state ^= 1 << 1;
                    break;
                case 'i':
                    state ^= 1 << 2;
                    break;
                case 'o':
                    state ^= 1 << 3;
                    break;
                case 'u':
                    state ^= 1 << 4;
                    break;
                default:
                    break;
            }

            if (pos[state] >= 0) {
                maxLen = Math.max(maxLen, i + 1 - pos[state]);
            } else {
                pos[state] = i + 1;
            }
        }

        return maxLen;          
    }
}
