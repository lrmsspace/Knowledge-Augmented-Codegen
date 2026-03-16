// Source: https://leetcode.com/problems/range-product-queries-of-powers/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, there exists a 0-indexed array called powers, composed of the minimum number of powers of 2 that sum to n. The array is sorted in non-decreasing order, and there is only one way to form the array.
//
// You are also given a 0-indexed 2D integer array queries, where queries[i] = [lefti, righti]. Each queries[i] represents a query where you have to find the product of all powers[j] with lefti <= j <= righti.
//
// Return an array answers, equal in length to queries, where answers[i] is the answer to the ith query. Since the answer to the ith query may be too large, each answers[i] should be returned modulo 109 + 7.
//
// Example:
// Input: n = 15, queries = [[0,1],[2,2],[0,3]]
// Output: [2,4,64]
// Explanation:
// For n = 15, powers = [1,2,4,8]. It can be shown that powers cannot be a smaller size.
// Answer to 1st query: powers[0] * powers[1] = 1 * 2 = 2.
// Answer to 2nd query: powers[2] = 4.
// Answer to 3rd query: powers[0] * powers[1] * powers[2] * powers[3] = 1 * 2 * 4 * 8 = 64.
// Each answer modulo 109 + 7 yields the same answer, so [2,4,64] is returned.
//
// Constraints:
// 1 <= n <= 109
// 	1 <= queries.length <= 105
// 	0 <= starti <= endi < powers.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productQueries(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    const int MOD = 1e9 + 7;
    int powers[32];
    int powerCount = 0;
    for (int i = 0; i < 32; ++i) {
        if (n & (1 << i)) {
            powers[powerCount++] = 1 << i;
        }
    }

    // Precompute prefix products modulo MOD
    long long prefixProducts[32];
    prefixProducts[0] = powers[0] % MOD;
    for (int i = 1; i < powerCount; ++i) {
        prefixProducts[i] = (prefixProducts[i - 1] * powers[i]) % MOD;
    }

    int* results = (int*)malloc(queriesSize * sizeof(int));
    for (int i = 0; i < queriesSize; ++i) {
        int left = queries[i][0];
        int right = queries[i][1];
        if (left == 0) {
            results[i] = (int)(prefixProducts[right] % MOD);
        } else {
            long long product = prefixProducts[right] * modInverse(prefixProducts[left - 1], MOD) % MOD;
            results[i] = (int)(product % MOD);
        }
    }

    *returnSize = queriesSize;
    return results;     
}
