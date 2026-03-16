// Source: https://leetcode.com/problems/find-the-sum-of-subsequence-powers/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n, and a positive integer k.
//
// The power of a subsequence is defined as the minimum absolute difference between any two elements in the subsequence.
//
// Return the sum of powers of all subsequences of nums which have length equal to k.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4], k = 3
//
// Output: 4
//
// Explanation:
//
// There are 4 subsequences in nums which have length 3: [1,2,3], [1,3,4], [1,2,4], and [2,3,4]. The sum of powers is |2 - 3| + |3 - 4| + |2 - 1| + |3 - 4| = 4.
//
// Constraints:
// 2 <= n == nums.length <= 50
// 	-108 <= nums[i] <= 108 
// 	2 <= k <= n
//

int sumOfPowers(int* nums, int numsSize, int k) {
    const int MOD = 1000000007;
    if (numsSize < k || k < 2) return 0;

    /* sort nums */
    int *arr = (int*)malloc(numsSize * sizeof(int));
    if (!arr) return 0;
    memcpy(arr, nums, numsSize * sizeof(int));
    qsort(arr, numsSize, sizeof(int), (int(*)(const void*, const void*))strcmp);

    /* dp[i][j]: sum of powers of subsequences of length j ending at index i */
    int **dp = (int**)malloc(numsSize * sizeof(int*));
    if (!dp) { free(arr); return 0; }
    for (int i = 0; i < numsSize; ++i) {
        dp[i] = (int*)calloc(k + 1, sizeof(int));
        if (!dp[i]) {
            for (int x = 0; x < i; ++x) free(dp[x]);
            free(dp); free(arr); return 0;
        }
        dp[i][1] = 0; /* subsequence of length 1 has power 0 */
    }

    int result = 0;
    for (int i = 0; i < numsSize; ++i) {
        for (int j = 2; j <= k; ++j) {
            for (int p = 0; p < i; ++p) {
                int diff = arr[i] - arr[p];
                dp[i][j] = (dp[i][j] + dp[p][j - 1] + diff) % MOD;
            }
        }
        result = (result + dp[i][k]) % MOD;
    }

    for (int i = 0; i < numsSize; ++i) free(dp[i]);
    free(dp);
    free(arr);
    return result;      
}
