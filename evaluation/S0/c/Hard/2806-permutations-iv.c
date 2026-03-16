// Source: https://leetcode.com/problems/permutations-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given two integers, n and k, an alternating permutation is a permutation of the first n positive integers such that no two adjacent elements are both odd or both even.
//
// Return the k-th alternating permutation sorted in lexicographical order. If there are fewer than k valid alternating permutations, return an empty list.
//
// Example:
// Input: n = 4, k = 6
//
// Output: [3,4,1,2]
//
// Explanation:
//
// The lexicographically-sorted alternating permutations of [1, 2, 3, 4] are:
//
//
// 	[1, 2, 3, 4]
// 	[1, 4, 3, 2]
// 	[2, 1, 4, 3]
// 	[2, 3, 4, 1]
// 	[3, 2, 1, 4]
// 	[3, 4, 1, 2] ← 6th permutation
// 	[4, 1, 2, 3]
// 	[4, 3, 2, 1]
//
//
// Since k = 6, we return [3, 4, 1, 2].
//
// Constraints:
// 1 <= n <= 100
// 	1 <= k <= 1015
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* permute(int n, long long k, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = 0;
    if (n <= 0 || k <= 0) return NULL;

    int *result = (int*)malloc(n * sizeof(int));
    if (!result) return NULL;

    int evenCount = n / 2;
    int oddCount = n - evenCount;

    long long dp[101][51][51];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int e = 0; e <= evenCount; ++e) {
            for (int o = 0; o <= oddCount; ++o) {
                if (e > 0) dp[i][e][o] += dp[i-1][e-1][o] * (e);
                if (o > 0) dp[i][e][o] += dp[i-1][e][o-1] * (o);
            }
        }
    }

    if (k > dp[n][evenCount][oddCount]) {
        free(result);
        return NULL;
    }

    int used[101] = {0};
    int e = evenCount, o = oddCount;

    for (int i = 0; i < n; ++i) {
        for (int num = 1; num <= n; ++num) {
            if (used[num]) continue;
            int isEven = (num % 2 == 0);
            if (isEven && e == 0) continue;
            if (!isEven && o == 0) continue;

            long long count;
            if (isEven) {
                count = dp[n - i - 1][e - 1][o];
            } else {
                count = dp[n - i - 1][e][o - 1];
            }

            if (k > count) {
                k -= count;
            } else {
                result[i] = num;
                used[num] = 1;
                if (isEven) e--;
                else o--;
                break;
            }
        }
    }

    *returnSize = n;
    return result;      
}
