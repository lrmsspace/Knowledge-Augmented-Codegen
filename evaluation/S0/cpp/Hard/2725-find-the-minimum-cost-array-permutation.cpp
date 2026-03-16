// Source: https://leetcode.com/problems/find-the-minimum-cost-array-permutation/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums which is a permutation of [0, 1, 2, ..., n - 1]. The score of any permutation of [0, 1, 2, ..., n - 1] named perm is defined as:
//
// score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] - nums[perm[0]]|
//
// Return the permutation perm which has the minimum possible score. If multiple permutations exist with this score, return the one that is lexicographically smallest among them.
//
// Example:
// Input: nums = [1,0,2]
//
// Output: [0,1,2]
//
// Explanation:
//
//
//
// The lexicographically smallest permutation with minimum cost is [0,1,2]. The cost of this permutation is |0 - 0| + |1 - 2| + |2 - 1| = 2.
//
// Constraints:
// 2 <= n == nums.length <= 14
// 	nums is a permutation of [0, 1, 2, ..., n - 1].
//

class Solution {
public:
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size();
        int N = 1 << n;
        vector<vector<long long>> dp(N, vector<long long>(n, 1e15));
        vector<vector<int>> parent(N, vector<int>(n, -1));
        
        // Initialize base cases
        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = 0;
        }
        
        // Fill DP table
        for (int mask = 1; mask < N; mask++) {
            for (int u = 0; u < n; u++) {
                if (!(mask & (1 << u))) continue;
                
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v)) continue;
                    
                    int nextMask = mask | (1 << v);
                    long long cost = dp[mask][u] + abs(v - nums[u]);
                    
                    if (cost < dp[nextMask][v]) {
                        dp[nextMask][v] = cost;
                        parent[nextMask][v] = u;
                    }
                }
            }
        }
        
        // Find minimum cost and last index
        long long minCost = 1e15;
        int lastIndex = -1;
        for (int i = 0; i < n; i++) {
            if (dp[N - 1][i] < minCost) {
                minCost = dp[N - 1][i];
                lastIndex = i;
            }
        }
        
        // Reconstruct permutation
        vector<int> perm(n);
        int mask = N - 1;
        for (int i = n - 1; i >= 0; i--) {
            perm[i] = lastIndex;
            int temp = lastIndex;
            lastIndex = parent[mask][lastIndex];
            mask ^= (1 << temp);
        }
        
        return perm;            
    }
};
