// Source: https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, and an integer k. The task is to find the maximum sum of at most k elements from the matrix grid such that:
//
//
// 	
// 	The number of elements taken from the ith row of grid does not exceed limits[i].
// 	
//
//
// Return the maximum sum.
//
// Example:
// Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
//
// Output: 7
//
// Explanation:
//
//
// 	From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
// 	The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.
//
// Constraints:
// n == grid.length == limits.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	0 <= grid[i][j] <= 105
// 	0 <= limits[i] <= m
// 	0 <= k <= min(n * m, sum(limits))
//

long long maxSum(int** grid, int gridSize, int* gridColSize, int* limits, int limitsSize, int k) {
    // Step 1: Preprocess each row to get the maximum sums for taking up to limits[i] elements
    long long** prefixSums = (long long**)malloc(gridSize * sizeof(long long*));
    for (int i = 0; i < gridSize; i++) {
        // Sort the row in descending order
        qsort(grid[i], gridColSize[i], sizeof(int), [](const void* a, const void* b) {
            return (*(int*)b - *(int*)a);
        });

        // Calculate prefix sums
        prefixSums[i] = (long long*)calloc(limits[i] + 1, sizeof(long long));
        for (int j = 1; j <= limits[i]; j++) {
            prefixSums[i][j] = prefixSums[i][j - 1] + grid[i][j - 1];
        }
    }

    // Step 2: Dynamic Programming to find the maximum sum with at most k elements
    long long* dp = (long long*)calloc(k + 1, sizeof(long long));

    for (int i = 0; i < gridSize; i++) {
        for (int j = k; j >= 0; j--) {
            for (int x = 1; x <= limits[i] && x <= j; x++) {
                dp[j] = fmax(dp[j], dp[j - x] + prefixSums[i][x]);
            }
        }
    }

    long long result = dp[k];

    // Free allocated memory
    for (int i = 0; i < gridSize; i++) {
        free(prefixSums[i]);
    }
    free(prefixSums);
    free(dp);

    return result;      
}
