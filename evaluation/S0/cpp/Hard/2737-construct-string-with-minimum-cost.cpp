// Source: https://leetcode.com/problems/construct-string-with-minimum-cost/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string target, an array of strings words, and an integer array costs, both arrays of the same length.
//
// Imagine an empty string s.
//
// You can perform the following operation any number of times (including zero):
//
//
// 	Choose an index i in the range [0, words.length - 1].
// 	Append words[i] to s.
// 	The cost of operation is costs[i].
//
//
// Return the minimum cost to make s equal to target. If it's not possible, return -1.
//
// Example:
// Input: target = "abcdef", words = ["abdef","abc","d","def","ef"], costs = [100,1,1,10,5]
//
// Output: 7
//
// Explanation:
//
// The minimum cost can be achieved by performing the following operations:
//
//
// 	Select index 1 and append "abc" to s at a cost of 1, resulting in s = "abc".
// 	Select index 2 and append "d" to s at a cost of 1, resulting in s = "abcd".
// 	Select index 4 and append "ef" to s at a cost of 5, resulting in s = "abcdef".
//
// Constraints:
// 1 <= target.length <= 5 * 104
// 	1 <= words.length == costs.length <= 5 * 104
// 	1 <= words[i].length <= target.length
// 	The total sum of words[i].length is less than or equal to 5 * 104.
// 	target and words[i] consist only of lowercase English letters.
// 	1 <= costs[i] <= 104
//

class Solution {
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        int n = target.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            for (size_t j = 0; j < words.size(); ++j) {
                const string& word = words[j];
                int len = word.size();
                if (i >= len && target.substr(i - len, len) == word && dp[i - len] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - len] + costs[j]);
                }
            }
        }
        
        return dp[n] == INT_MAX ? -1 : dp[n];           
    }
};
