// Source: https://leetcode.com/problems/tallest-billboard/   |   Difficulty: Hard
//
// Problem Description:
// You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.
//
// You are given a collection of rods that can be welded together. For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.
//
// Return the largest possible height of your billboard installation. If you cannot support the billboard, return 0.
//
// Example:
// Input: rods = [1,2,3,6]
// Output: 6
// Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
//
// Constraints:
// 1 <= rods.length <= 20
// 	1 <= rods[i] <= 1000
// 	sum(rods[i]) <= 5000
//

class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        int maxSum = 0;
        for (int rod : rods) {
            maxSum += rod;
        }
        
        vector<int> dp(2 * maxSum + 1, -1);
        dp[maxSum] = 0;  // base case: difference 0, height 0
        
        for (int rod : rods) {
            vector<int> newDp = dp;
            for (int diff = 0; diff <= 2 * maxSum; diff++) {
                if (dp[diff] < 0) continue;
                
                // Add rod to left support
                if (diff + rod <= 2 * maxSum) {
                    newDp[diff + rod] = max(newDp[diff + rod], dp[diff]);
                }
                
                // Add rod to right support
                if (diff - rod >= 0) {
                    newDp[diff - rod] = max(newDp[diff - rod], dp[diff] + rod);
                }
            }
            dp = newDp;
        }
        
        return dp[maxSum];          
    }
};
