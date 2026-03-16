// Source: https://leetcode.com/problems/extra-characters-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string s and a dictionary of words dictionary. You have to break s into one or more non-overlapping substrings such that each substring is present in dictionary. There may be some extra characters in s which are not present in any of the substrings.
//
// Return the minimum number of extra characters left over if you break up s optimally.
//
// Example:
// Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
// Output: 1
// Explanation: We can break s in two substrings: "leet" from index 0 to 3 and "code" from index 5 to 8. There is only 1 unused character (at index 4), so we return 1.
//
// Constraints:
// 1 <= s.length <= 50
// 	1 <= dictionary.length <= 50
// 	1 <= dictionary[i].length <= 50
// 	dictionary[i] and s consists of only lowercase English letters
// 	dictionary contains distinct words
//

class Solution {
    public int minExtraChar(String s, String[] dictionary) {
        int n = s.length();
        int[] dp = new int[n + 1];
        dp[n] = 0; // Base case: no extra characters needed for an empty substring

        for (int i = n - 1; i >= 0; i--) {
            dp[i] = dp[i + 1] + 1; // Assume the current character is extra
            for (String word : dictionary) {
                int len = word.length();
                if (i + len <= n && s.substring(i, i + len).equals(word)) {
                    dp[i] = Math.min(dp[i], dp[i + len]); // Update dp[i] if we find a matching word
                }
            }
        }

        return dp[0]; // Minimum extra characters for the whole string          
    }
}
