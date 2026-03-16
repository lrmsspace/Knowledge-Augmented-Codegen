// Source: https://leetcode.com/problems/distinct-echo-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
//
// Example:
// Input: text = "abcabcabc"
// Output: 3
// Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
//
// Constraints:
// 1 <= text.length <= 2000
// 	text has only lowercase English letters.
//

class Solution {
    public int distinctEchoSubstrings(String text) {
        int n = text.length();
        boolean[][] dp = new boolean[n][n];
        Set<String> set = new HashSet<>();

        for (int length = 1; length <= n / 2; length++) {
            for (int i = 0; i + 2 * length <= n; i++) {
                int j = i + length;
                if (text.charAt(i) == text.charAt(j)) {
                    if (length == 1 || dp[i + 1][j + 1]) {
                        dp[i][j] = true;
                        set.add(text.substring(i, i + 2 * length));
                    }
                }
            }
        }

        return set.size();                  
    }
}
