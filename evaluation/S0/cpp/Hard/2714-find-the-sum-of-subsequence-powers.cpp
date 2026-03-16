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

class Solution {
public:
    int sumOfPowers(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        // Precompute combinations
        vector<vector<long long>> comb(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            comb[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }
        
        long long result = 0;
        
        // Iterate over all pairs (i, j) where i < j
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int diff = nums[j] - nums[i];
                
                // Count elements between nums[i] and nums[j]
                int betweenCount = j - i - 1;
                
                // We need to choose (k - 2) elements from the betweenCount
                if (betweenCount >= k - 2) {
                    long long ways = comb[betweenCount][k - 2];
                    result = (result + ways * diff) % MOD;
                }
            }
        }
        
        return (int)result;         
    }
};
