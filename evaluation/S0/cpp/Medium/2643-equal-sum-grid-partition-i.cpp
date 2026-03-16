// Source: https://leetcode.com/problems/equal-sum-grid-partition-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
//
//
// 	Each of the two resulting sections formed by the cut is non-empty.
// 	The sum of the elements in both sections is equal.
//
//
// Return true if such a partition exists; otherwise return false.
//
// Example:
// Input: grid = [[1,4],[2,3]]
//
// Output: true
//
// Explanation:
//
//
//
// A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.
//
// Constraints:
// 1 <= m == grid.length <= 105
// 	1 <= n == grid[i].length <= 105
// 	2 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        long long totalSum = 0;
        for (const auto& row : grid) {
            for (int val : row) {
                totalSum += val;
            }
        }

        if (totalSum % 2 != 0) {
            return false;
        }

        long long halfSum = totalSum / 2;

        // Check for horizontal cut
        long long rowSum = 0;
        for (const auto& row : grid) {
            for (int val : row) {
                rowSum += val;
            }
            if (rowSum == halfSum) {
                return true;
            }
        }

        // Check for vertical cut
        int n = grid[0].size();
        vector<long long> colSums(n, 0);
        for (const auto& row : grid) {
            for (int j = 0; j < n; ++j) {
                colSums[j] += row[j];
            }
        }

        long long cumulativeColSum = 0;
        for (long long colSum : colSums) {
            cumulativeColSum += colSum;
            if (cumulativeColSum == halfSum) {
                return true;
            }
        }

        return false;           
    }
};
