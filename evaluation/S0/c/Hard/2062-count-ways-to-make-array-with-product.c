// Source: https://leetcode.com/problems/count-ways-to-make-array-with-product/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array, queries. For each queries[i], where queries[i] = [ni, ki], find the number of different ways you can place positive integers into an array of size ni such that the product of the integers is ki. As the number of ways may be too large, the answer to the ith query is the number of ways modulo 109 + 7.
//
// Return an integer array answer where answer.length == queries.length, and answer[i] is the answer to the ith query.
//
// Example:
// Input: queries = [[2,6],[5,1],[73,660]]
// Output: [4,1,50734910]
// Explanation: Each query is independent.
// [2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
// [5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
// [73,660]: There are 1050734917 ways to fill an array of size 73 that multiply to 660. 1050734917 modulo 109 + 7 = 50734910.
//
// Constraints:
// 1 <= queries.length <= 104 
// 	1 <= ni, ki <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* waysToFillArray(int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    const int MOD = 1000000007;

    /* Precompute factorials and inverse factorials for combinations */
    int maxN = 20000; /* since ni and ki can be up to 10^4, we need up to 2*10^4 for combinations */
    long long *fact = (long long*)malloc((maxN + 1) * sizeof(long long));
    long long *invFact = (long long*)malloc((maxN + 1) * sizeof(long long));
    if (!fact || !invFact) {
        free(fact); free(invFact);
        return NULL;
    }
    fact[0] = 1;
    for (int i = 1; i <= maxN; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[maxN] = 1; /* Fermat's little theorem for modular inverse */
    long long base = fact[maxN];
    long long exp = MOD - 2;
    while (exp) {
        if (exp % 2) invFact[maxN] = (invFact[maxN] * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    for (int i = maxN - 1; i >= 0; --i) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) {
        free(fact); free(invFact);
        return NULL;
    }

    for (int q = 0; q < queriesSize; ++q) {
        int n = queries[q][0];
        int k = queries[q][1];

        /* Prime factorization of k */
        int tempK = k;
        long long ways = 1;
        for (int p = 2; p * p <= tempK; ++p) {
            if (tempK % p == 0) {
                int count = 0;
                while (tempK % p == 0) {
                    tempK /= p;
                    count++;
                }
                /* Calculate combinations: C(n + count - 1, count) */       
                ways = (ways * fact[n + count - 1]) % MOD;
                ways = (ways * invFact[count]) % MOD;
                ways = (ways * invFact[n - 1]) % MOD;
            }
        }
        if (tempK > 1) {
            /* tempK is prime */
            ways = (ways * fact[n + 1 - 1]) % MOD;
            ways = (ways * invFact[1]) % MOD;
            ways = (ways * invFact[n - 1]) % MOD;
        }
        results[q] = (int)ways;
    }
    free(fact);
    free(invFact);
    *returnSize = queriesSize;
    return results;
}