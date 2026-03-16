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
    public int minMaxSums(int[] nums, int k) {
        Arrays.sort(nums);
        int n = nums.length;
        long mod = 1_000_000_007;
        long result = 0;

        long[] pow2 = new long[k + 1];
        pow2[0] = 1;
        for (int i = 1; i <= k; i++) {
            pow2[i] = (pow2[i - 1] * 2) % mod;
        }

        for (int i = 0; i < n; i++) {
            int maxCount = Math.min(i, k - 1);
            int minCount = Math.min(n - 1 - i, k - 1);

            if (maxCount >= 0) {
                result = (result + nums[i] * pow2[maxCount]) % mod;
            }
            if (minCount >= 0) {
                result = (result + nums[i] * pow2[minCount]) % mod;
            }
        }

        return (int) result;            
    }
}
