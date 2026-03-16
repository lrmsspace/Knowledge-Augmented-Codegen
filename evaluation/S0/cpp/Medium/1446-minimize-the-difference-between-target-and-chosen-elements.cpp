// Source: https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix mat and an integer target.
//
// Choose one integer from each row in the matrix such that the absolute difference between target and the sum of the chosen elements is minimized.
//
// Return the minimum absolute difference.
//
// The absolute difference between two numbers a and b is the absolute value of a - b.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], target = 13
// Output: 0
// Explanation: One possible choice is to:
// - Choose 1 from the first row.
// - Choose 5 from the second row.
// - Choose 7 from the third row.
// The sum of the chosen elements is 13, which equals the target, so the absolute difference is 0.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 70
// 	1 <= mat[i][j] <= 70
// 	1 <= target <= 800
//

class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        int m = mat.size();
        int n = mat[0].size();
        vector<bitset<4901>> dp(m);
        
        for (int j = 0; j < n; ++j) {
            dp[0][mat[0][j]] = 1;
        }
        
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int val = mat[i][j];
                dp[i] |= (dp[i-1] << val);
            }
        }
        
        int ans = INT_MAX;
        for (int sum = 0; sum <= 4900; ++sum) {
            if (dp[m-1][sum]) {
                ans = min(ans, abs(sum - target));
            }
        }
        
        return ans;         
    }
};
