// Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings words and a string target.
//
// A string x is called valid if x is a prefix of any string in words.
//
// Return the minimum number of valid strings that can be concatenated to form target. If it is not possible to form target, return -1.
//
// Example:
// Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"
//
// Output: 3
//
// Explanation:
//
// The target string can be formed by concatenating:
//
//
// 	Prefix of length 2 of words[1], i.e. "aa".
// 	Prefix of length 3 of words[2], i.e. "bcd".
// 	Prefix of length 3 of words[0], i.e. "abc".
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 5 * 103
// 	The input is generated such that sum(words[i].length) <= 105.
// 	words[i] consists only of lowercase English letters.
// 	1 <= target.length <= 5 * 103
// 	target consists only of lowercase English letters.
//

class Solution {
    public int minValidStrings(String[] words, String target) {
        int n = target.length();
        int[] dp = new int[n + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            for (String word : words) {
                int len = word.length();
                if (i >= len && target.substring(i - len, i).equals(word)) {
                    if (dp[i - len] != Integer.MAX_VALUE) {
                        dp[i] = Math.min(dp[i], dp[i - len] + 1);
                    }
                }
            }
        }

        return dp[n] == Integer.MAX_VALUE ? -1 : dp[n];         
    }
}
