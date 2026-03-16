// Source: https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/   |   Difficulty: Hard
//
// Problem Description:
// You are given a list of strings of the same length words and a string target.
//
// Your task is to form target using the given words under the following rules:
//
//
// 	target should be formed from left to right.
// 	To form the ith character (0-indexed) of target, you can choose the kth character of the jth string in words if target[i] = words[j][k].
// 	Once you use the kth character of the jth string of words, you can no longer use the xth character of any string in words where x <= k. In other words, all characters to the left of or at index k become unusuable for every string.
// 	Repeat the process until you form the string target.
//
//
// Notice that you can use multiple characters from the same string in words provided the conditions above are met.
//
// Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: words = ["acca","bbbb","caca"], target = "aba"
// Output: 6
// Explanation: There are 6 ways to form target.
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 1000
// 	All strings in words have the same length.
// 	1 <= target.length <= 1000
// 	words[i] and target contain only lowercase English letters.
//

class Solution {
    public int numWays(String[] words, String target) {
        int MOD = 1_000_000_007;
        int wordLen = words[0].length();
        int targetLen = target.length();

        // Precompute frequency of each character at each position
        int[][] charCount = new int[wordLen][26];
        for (String word : words) {
            for (int i = 0; i < wordLen; i++) {
                charCount[i][word.charAt(i) - 'a']++;
            }
        }

        // DP array to store the number of ways to form target up to index j using first i characters
        long[][] dp = new long[wordLen + 1][targetLen + 1];
        dp[0][0] = 1; // Base case: one way to form an empty target

        for (int i = 1; i <= wordLen; i++) {
            for (int j = 0; j <= targetLen; j++) {
                // Option 1: Skip the current character position
                dp[i][j] = dp[i - 1][j];

                // Option 2: Use the current character position if it matches the target character
                if (j > 0) {
                    char targetChar = target.charAt(j - 1);
                    dp[i][j] += dp[i - 1][j - 1] * charCount[i - 1][targetChar - 'a'];
                    dp[i][j] %= MOD;
                }
            }
        }

        return (int) dp[wordLen][targetLen];                    
    }
}
