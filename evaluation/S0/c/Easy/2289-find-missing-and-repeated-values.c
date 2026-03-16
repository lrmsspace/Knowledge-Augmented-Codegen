// Source: https://leetcode.com/problems/find-missing-and-repeated-values/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed 2D integer matrix grid of size n * n with values in the range [1, n2]. Each integer appears exactly once except a which appears twice and b which is missing. The task is to find the repeating and missing numbers a and b.
//
// Return a 0-indexed integer array ans of size 2 where ans[0] equals to a and ans[1] equals to b.
//
// Example:
// Input: grid = [[1,3],[2,2]]
// Output: [2,4]
// Explanation: Number 2 is repeated and number 4 is missing so the answer is [2,4].
//
// Constraints:
// 2 <= n == grid.length == grid[i].length <= 50
// 	1 <= grid[i][j] <= n * n
// 	For all x that 1 <= x <= n * n there is exactly one x that is not equal to any of the grid members.
// 	For all x that 1 <= x <= n * n there is exactly one x that is equal to exactly two of the grid members.
// 	For all x that 1 <= x <= n * n except two of them there is exactly one pair of i, j that 0 <= i, j <= n - 1 and grid[i][j] == x.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMissingAndRepeatedValues(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int n = gridSize;
    int totalNumbers = n * n;
    int expectedSum = (totalNumbers * (totalNumbers + 1)) / 2;
    int expectedSumSquares = (totalNumbers * (totalNumbers + 1) * (2 * totalNumbers + 1)) / 6;

    int actualSum = 0;
    int actualSumSquares = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num = grid[i][j];
            actualSum += num;
            actualSumSquares += num * num;
        }
    }

    int sumDiff = expectedSum - actualSum; // b - a
    int sumSquaresDiff = expectedSumSquares - actualSumSquares; // b^2 - a^2

    // b^2 - a^2 = (b - a)(b + a)
    // => b + a = sumSquaresDiff / sumDiff
    int sumPlus = sumSquaresDiff / sumDiff;

    // Now we have two equations:
    // 1. b - a = sumDiff
    // 2. b + a = sumPlus

    // Solving these two equations:
    // Adding both equations:
    // 2b = sumDiff + sumPlus
    // => b = (sumDiff + sumPlus) / 2
    int b = (sumDiff + sumPlus) / 2;

    // Substituting b in the first equation:
    // a = b - sumDiff
    int a = b - sumDiff;

    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = a; // Repeated number
    result[1] = b; // Missing number
    *returnSize = 2;
    
    return result;      
}
