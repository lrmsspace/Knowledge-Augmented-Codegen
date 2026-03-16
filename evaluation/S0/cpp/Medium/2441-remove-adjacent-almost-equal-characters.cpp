// Source: https://leetcode.com/problems/remove-adjacent-almost-equal-characters/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string word.
//
// In one operation, you can pick any index i of word and change word[i] to any lowercase English letter.
//
// Return the minimum number of operations needed to remove all adjacent almost-equal characters from word.
//
// Two characters a and b are almost-equal if a == b or a and b are adjacent in the alphabet.
//
// Example:
// Input: word = "aaaaa"
// Output: 2
// Explanation: We can change word into "acaca" which does not have any adjacent almost-equal characters.
// It can be shown that the minimum number of operations needed to remove all adjacent almost-equal characters from word is 2.
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists only of lowercase English letters.
//

class Solution {
public:
    int removeAlmostEqualCharacters(string word) {
        int n = word.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            // Option 1: Change current character
            dp[i] = dp[i - 1] + 1;

            // Option 2: Keep current character if not almost-equal to previous
            if (i == 1 || !isAlmostEqual(word[i - 1], word[i - 2])) {
                dp[i] = min(dp[i], dp[i - 1]);
            }
        }

        return dp[n];           
    }
};
