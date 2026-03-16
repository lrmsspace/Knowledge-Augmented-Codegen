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

class Solution {
    public int[] productQueries(int n, int[][] queries) {
        final int MOD = 1_000_000_007;

        // Step 1: Decompose n into powers of 2
        List<Long> powers = new ArrayList<>();
        for (int i = 0; i < 31; i++) {
            if ((n & (1 << i)) != 0) {
                powers.add((long)(1 << i));
            }
        }

        // Step 2: Precompute prefix products modulo MOD
        int m = powers.size();
        long[] prefixProducts = new long[m + 1];
        prefixProducts[0] = 1;
        for (int i = 1; i <= m; i++) {
            prefixProducts[i] = (prefixProducts[i - 1] * powers.get(i - 1)) % MOD;
        }

        // Step 3: Process each query
        int q = queries.length;
        int[] results = new int[q];
        for (int i = 0; i < q; i++) {
            int left = queries[i][0];
            int right = queries[i][1];
            long product = prefixProducts[right + 1] * modInverse(prefixProducts[left], MOD) % MOD;
            results[i] = (int) product;
        }

        return results;         
    }
}
