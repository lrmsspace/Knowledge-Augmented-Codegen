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
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        vector<int> powers;
        for (int i = 0; (1 << i) <= n; ++i) {
            if (n & (1 << i)) {
                powers.push_back(1 << i);
            }
        }

        int m = powers.size();
        vector<long long> prefixProduct(m + 1, 1);
        for (int i = 0; i < m; ++i) {
            prefixProduct[i + 1] = (prefixProduct[i] * powers[i]) % MOD;
        }

        vector<int> result;
        for (const auto& query : queries) {
            int left = query[0];
            int right = query[1];
            long long prod = prefixProduct[right + 1] * modInverse(prefixProduct[left], MOD) % MOD;
            result.push_back(static_cast<int>(prod));
        }

        return result;          
    }
};
