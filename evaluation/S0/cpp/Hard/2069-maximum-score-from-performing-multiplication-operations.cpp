// Source: https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums and multipliers of size n and m respectively, where n >= m.
//
// You begin with a score of 0. You want to perform exactly m operations. On the ith operation (0-indexed) you will:
//
//
//     Choose one integer x from either the start or the end of the array nums.
//     Add multipliers[i] * x to your score.
//     
//         Note that multipliers[0] corresponds to the first operation, multipliers[1] to the second operation, and so on.
//     
//     
//     Remove x from nums.
//
//
// Return the maximum score after performing m operations.
//
// Example:
// Input: nums = [1,2,3], multipliers = [3,2,1]
// Output: 14
// Explanation: An optimal solution is as follows:
// - Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
// - Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
// - Choose from the end, [1], adding 1 * 1 = 1 to the score.
// The total score is 9 + 4 + 1 = 14.
//
// Constraints:
// n == nums.length
// 	m == multipliers.length
// 	1 <= m <= 300
// 	m <= n <= 105 
// 	-1000 <= nums[i], multipliers[i] <= 1000
//

class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size();
        int m = multipliers.size();
        vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));
        
        for (int op = m - 1; op >= 0; --op) {
            for (int left = op; left >= 0; --left) {
                int mult = multipliers[op];
                int right = n - 1 - (op - left);
                
                dp[op][left] = max(
                    mult * nums[left] + dp[op + 1][left + 1],
                    mult * nums[right] + dp[op + 1][left]
                );
            }
        }
        
        return dp[0][0];            
    }
};
