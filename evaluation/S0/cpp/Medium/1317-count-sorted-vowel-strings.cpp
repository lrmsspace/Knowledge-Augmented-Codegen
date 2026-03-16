// Source: https://leetcode.com/problems/count-sorted-vowel-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
//
// A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
//
// Constraints:
// 1 <= n <= 50
//

class Solution {
public:
    int countVowelStrings(int n) {
        // dp[i][j]: number of strings of length i that end with the j-th vowel
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));

        // Base case: for length 1, there's one string for each vowel
        for (int j = 0; j < 5; ++j) {
            dp[1][j] = 1;
        }

        // Fill the DP table
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < 5; ++j) {
                // Sum all strings of length i-1 that end with vowels up to j
                for (int k = 0; k <= j; ++k) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }

        // Sum all strings of length n
        int result = 0;
        for (int j = 0; j < 5; ++j) {
            result += dp[n][j];
        }

        return result;          
    }
};
