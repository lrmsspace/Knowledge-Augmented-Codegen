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

class Solution {
public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        const int MAX = 20000;
        
        // Precompute factorials and inverse factorials for combinations
        vector<long long> fact(MAX + 1, 1), invFact(MAX + 1, 1);
        for (int i = 1; i <= MAX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invFact[MAX] = modInverse(fact[MAX], MOD);
        for (int i = MAX - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }
        
        vector<int> result;
        
        for (const auto& query : queries) {
            int n = query[0];
            int k = query[1];
            
            // Prime factorization of k
            unordered_map<int, int> primeCount;
            for (int p = 2; p * p <= k; p++) {
                while (k % p == 0) {
                    primeCount[p]++;
                    k /= p;
                }
            }
            if (k > 1) {
                primeCount[k]++;
            }
            
            long long ways = 1;
            for (const auto& [prime, count] : primeCount) {
                // Calculate combinations: C(n + count - 1, count)
                ways = ways * comb(n + count - 1, count, fact, invFact, MOD) % MOD;
            }
            
            result.push_back((int)ways);
        }
        
        return result;          
    }
};
