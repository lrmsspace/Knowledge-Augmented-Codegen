// Source: https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n matrix mat that has its rows sorted in non-decreasing order and an integer k.
//
// You are allowed to choose exactly one element from each row to form an array.
//
// Return the kth smallest array sum among all possible arrays.
//
// Example:
// Input: mat = [[1,3,11],[2,4,6]], k = 5
// Output: 7
// Explanation: Choosing one element from each row, the first k smallest sum are:
// [1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.
//
// Constraints:
// m == mat.length
// 	n == mat.length[i]
// 	1 <= m, n <= 40
// 	1 <= mat[i][j] <= 5000
// 	1 <= k <= min(200, nm)
// 	mat[i] is a non-decreasing array.
//

int kthSmallest(int** mat, int matSize, int* matColSize, int k) {
    int maxSum = 0;
    for (int i = 0; i < matSize; ++i) {
        maxSum += mat[i][(*matColSize) - 1];
    }
    int *dp = (int*)calloc(maxSum + 1, sizeof(int));
    if (!dp) return -1; /* allocation failure */
    dp[0] = 1; /* base case */

    for (int i = 0; i < matSize; ++i) {
        int *newDp = (int*)calloc(maxSum + 1, sizeof(int));
        if (!newDp) { free(dp); return -1; } /* allocation failure */
        for (int sum = 0; sum <= maxSum; ++sum) {
            if (dp[sum]) {
                for (int j = 0; j < (*matColSize); ++j) {
                    int newSum = sum + mat[i][j];
                    newDp[newSum] += dp[sum];
                }
            }
        }
        free(dp);
        dp = newDp;
    }

    int count = 0;
    int result = -1;
    for (int sum = 0; sum <= maxSum; ++sum) {
        if (dp[sum]) {
            count += dp[sum];
            if (count >= k) {
                result = sum;
                break;
            }
        }
    }

    free(dp);
    return result;      
}
