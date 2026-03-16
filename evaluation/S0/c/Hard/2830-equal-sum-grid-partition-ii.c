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

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    long long total = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            total += grid[i][j];
        }
    }
    if (total % 2 != 0) return false;
    long long half = total / 2;

    // Check horizontal cuts
    long long prefixSum = 0;
    for (int i = 0; i < m - 1; ++i) {
        for (int j = 0; j < n; ++j) {
            prefixSum += grid[i][j];
        }
        if (prefixSum == half) return true;
    }

    // Check vertical cuts
    prefixSum = 0;
    for (int j = 0; j < n - 1; ++j) {
        for (int i = 0; i < m; ++i) {
            prefixSum += grid[i][j];
        }
        if (prefixSum == half) return true;
    }

    return false;       
}
