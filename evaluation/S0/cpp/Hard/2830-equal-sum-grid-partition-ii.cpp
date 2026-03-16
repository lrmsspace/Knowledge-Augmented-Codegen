// Source: https://leetcode.com/problems/equal-sum-grid-partition-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
//
//
// 	Each of the two resulting sections formed by the cut is non-empty.
// 	The sum of elements in both sections is equal, or can be made equal by discounting at most one single cell in total (from either section).
// 	If a cell is discounted, the rest of the section must remain connected.
//
//
// Return true if such a partition exists; otherwise, return false.
//
// Note: A section is connected if every cell in it can be reached from any other cell by moving up, down, left, or right through other cells in the section.
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
//
// 	A horizontal cut after the first row gives sums 1 + 4 = 5 and 2 + 3 = 5, which are equal. Thus, the answer is true.
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
        int m = grid.size();
        int n = grid[0].size();
        vector<long long> rowSum(m, 0);
        vector<long long> colSum(n, 0);
        long long totalSum = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowSum[i] += grid[i][j];
                colSum[j] += grid[i][j];
                totalSum += grid[i][j];
            }
        }

        for (int i = 0; i < m - 1; ++i) {
            long long topSum = accumulate(rowSum.begin(), rowSum.begin() + i + 1, 0LL);
            long long bottomSum = totalSum - topSum;
            if (topSum == bottomSum) return true;
            if (abs(topSum - bottomSum) <= 105) return true;
        }

        for (int j = 0; j < n - 1; ++j) {
            long long leftSum = accumulate(colSum.begin(), colSum.begin() + j + 1, 0LL);
            long long rightSum = totalSum - leftSum;
            if (leftSum == rightSum) return true;
            if (abs(leftSum - rightSum) <= 105) return true;
        }

        return false;           
    }
};
