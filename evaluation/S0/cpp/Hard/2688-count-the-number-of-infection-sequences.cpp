// Source: https://leetcode.com/problems/count-the-number-of-infection-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an array sick sorted in increasing order, representing positions of infected people in a line of n people.
//
// At each step, one uninfected person adjacent to an infected person gets infected. This process continues until everyone is infected.
//
// An infection sequence is the order in which uninfected people become infected, excluding those initially infected.
//
// Return the number of different infection sequences possible, modulo 109+7.
//
// Example:
// Input: n = 5, sick = [0,4]
//
// Output: 4
//
// Explanation:
//
// There is a total of 6 different sequences overall.
//
//
// 	Valid infection sequences are [1,2,3], [1,3,2], [3,2,1] and [3,1,2].
// 	[2,3,1] and [2,1,3] are not valid infection sequences because the person at index 2 cannot be infected at the first step.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= sick.length <= n - 1
// 	0 <= sick[i] <= n - 1
// 	sick is sorted in increasing order.
//

class Solution {
public:
    int numberOfSequence(int n, vector<int>& sick) {
        const int MOD = 1e9 + 7;
        int m = sick.size();
        vector<long long> fact(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }
        
        auto modInverse = [&](long long a, long long mod) {
            long long m0 = mod, t, q;
            long long x0 = 0, x1 = 1;
            if (mod == 1) return 0LL;
            while (a > 1) {
                q = a / mod;
                t = mod;
                mod = a % mod, a = t;
                t = x0;
                x0 = x1 - q * x0;
                x1 = t;
            }
            if (x1 < 0) x1 += m0;
            return x1;
        };
        
        auto nCr = [&](int n, int r) {
            if (r > n || r < 0) return 0LL;
            long long res = fact[n];
            res = (res * modInverse(fact[r], MOD)) % MOD;
            res = (res * modInverse(fact[n - r], MOD)) % MOD;
            return res;
        };
        
        long long result = 1;
        for (int i = 0; i <= m; i++) {
            int left = (i == 0) ? sick[i] : sick[i] - sick[i - 1] - 1;
            int right = (i == m - 1) ? n - 1 - sick[i] : sick[i + 1] - sick[i] - 1;
            int len = left + right;
            
            result = (result * nCr(len, left)) % MOD;
            if (i > 0 && i < m - 1) {
                // Middle segment
                result = (result * fact[len - 1]) % MOD;
            } else {
                result = (result * fact[len]) % MOD;
            }
        }
        
        return (int)result;         
    }
};
