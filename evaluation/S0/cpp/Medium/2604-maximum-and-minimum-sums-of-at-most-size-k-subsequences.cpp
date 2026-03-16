// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subsequences of nums with at most k elements.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 24
//
// Explanation:
//
// The subsequences of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subsequence 
// 			Minimum
// 			Maximum
// 			Sum
// 		
// 		
// 			[1]
// 			1
// 			1
// 			2
// 		
// 		
// 			[2]
// 			2
// 			2
// 			4
// 		
// 		
// 			[3]
// 			3
// 			3
// 			6
// 		
// 		
// 			[1, 2]
// 			1
// 			2
// 			3
// 		
// 		
// 			[1, 3]
// 			1
// 			3
// 			4
// 		
// 		
// 			[2, 3]
// 			2
// 			3
// 			5
// 		
// 		
// 			Final Total
// 			 
// 			 
// 			24
// 		
// 	
//
//
// The output would be 24.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	1 <= k <= min(70, nums.length)
//

class Solution {
public:
    int minMaxSums(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        // Precompute powers of 2 up to n
        vector<long long> pow2(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        long long totalSum = 0;

        for (int i = 0; i < n; ++i) {
            // Count of subsequences where nums[i] is the minimum
            if (i < k) {
                totalSum = (totalSum + nums[i] * pow2[i]) % MOD;
            }

            // Count of subsequences where nums[i] is the maximum
            if (n - 1 - i < k) {
                totalSum = (totalSum + nums[i] * pow2[n - 1 - i]) % MOD;
            }
        }

        return static_cast<int>(totalSum);          
    }
};
