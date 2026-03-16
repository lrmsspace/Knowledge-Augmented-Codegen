// Source: https://leetcode.com/problems/count-of-interesting-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums, an integer modulo, and an integer k.
//
// Your task is to find the count of subarrays that are interesting.
//
// A subarray nums[l..r] is interesting if the following condition holds:
//
//
// 	Let cnt be the number of indices i in the range [l, r] such that nums[i] % modulo == k. Then, cnt % modulo == k.
//
//
// Return an integer denoting the count of interesting subarrays. 
//
// Note: A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [3,2,4], modulo = 2, k = 1
// Output: 3
// Explanation: In this example the interesting subarrays are: 
// The subarray nums[0..0] which is [3]. 
// - There is only one index, i = 0, in the range [0, 0] that satisfies nums[i] % modulo == k. 
// - Hence, cnt = 1 and cnt % modulo == k.  
// The subarray nums[0..1] which is [3,2].
// - There is only one index, i = 0, in the range [0, 1] that satisfies nums[i] % modulo == k.  
// - Hence, cnt = 1 and cnt % modulo == k.
// The subarray nums[0..2] which is [3,2,4]. 
// - There is only one index, i = 0, in the range [0, 2] that satisfies nums[i] % modulo == k. 
// - Hence, cnt = 1 and cnt % modulo == k. 
// It can be shown that there are no other interesting subarrays. So, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 105 
// 	1 <= nums[i] <= 109
// 	1 <= modulo <= 109
// 	0 <= k < modulo
//

class Solution {
    public long countInterestingSubarrays(List<Integer> nums, int modulo, int k) {
        Map<Integer, Long> prefixCount = new HashMap<>();
        prefixCount.put(0, 1L); // Base case: empty prefix

        long interestingSubarrays = 0;
        int currentPrefixMod = 0;

        for (int num : nums) {
            // Update currentPrefixMod based on whether num % modulo == k
            if (num % modulo == k) {
                currentPrefixMod = (currentPrefixMod + 1) % modulo;
            }

            // Calculate the target prefix mod we need to find
            int targetMod = (currentPrefixMod - k + modulo) % modulo;

            // If there are previous prefixes with the target mod, add their count
            interestingSubarrays += prefixCount.getOrDefault(targetMod, 0L);

            // Update the count of the current prefix mod
            prefixCount.put(currentPrefixMod, prefixCount.getOrDefault(currentPrefixMod, 0L) + 1);
        }

        return interestingSubarrays;            
    }
}
