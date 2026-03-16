// Source: https://leetcode.com/problems/triangle/   |   Difficulty: Medium
//
// Problem Description:
// Given a triangle array, return the minimum path sum from top to bottom.
//
// For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.
//
// Example:
// Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
// Output: 11
// Explanation: The triangle looks like:
//    2
//   3 4
//  6 5 7
// 4 1 8 3
// The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
//
// Constraints:
// 1 <= triangle.length <= 200
// 	triangle[0].length == 1
// 	triangle[i].length == triangle[i - 1].length + 1
// 	-104 <= triangle[i][j] <= 104
//
//
//  
// Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
//

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }

        return dp[0];           
    }
};
