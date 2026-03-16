// Source: https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums of non-negative integers, and two integers l and r.
//
// Return the count of sub-multisets within nums where the sum of elements in each subset falls within the inclusive range of [l, r].
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A sub-multiset is an unordered collection of elements of the array in which a given value x can occur 0, 1, ..., occ[x] times, where occ[x] is the number of occurrences of x in the array.
//
// Note that:
//
//
// 	Two sub-multisets are the same if sorting both sub-multisets results in identical multisets.
// 	The sum of an empty multiset is 0.
//
// Example:
// Input: nums = [1,2,2,3], l = 6, r = 6
// Output: 1
// Explanation: The only subset of nums that has a sum of 6 is {1, 2, 3}.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	0 <= nums[i] <= 2 * 104
// 	Sum of nums does not exceed 2 * 104.
// 	0 <= l <= r <= 2 * 104
//

class Solution {
public:
    int countSubMultisets(vector<int>& nums, int l, int r) {
        const int MOD = 1e9 + 7;
        int maxSum = accumulate(nums.begin(), nums.end(), 0);
        vector<int> freq(maxSum + 1, 0);
        for (int num : nums) {
            freq[num]++;
        }
        
        vector<long long> dp(maxSum + 1, 0);
        dp[0] = 1;  // empty multiset
        
        for (int val = 0; val <= maxSum; val++) {
            if (freq[val] == 0) continue;
            vector<long long> newDp(dp);
            for (int sum = 0; sum <= maxSum - val; sum++) {
                if (dp[sum] == 0) continue;
                long long ways = 1;
                for (int count = 1; count <= freq[val]; count++) {
                    ways = (ways * (freq[val] - count + 1)) % MOD;
                    newDp[sum + count * val] = (newDp[sum + count * val] + dp[sum] * ways) % MOD;
                }
            }
            dp = newDp;
        }
        
        long long result = 0;
        for (int sum = l; sum <= r; sum++) {
            result = (result + dp[sum]) % MOD;
        }
        
        return (int)result;         
    }
};
