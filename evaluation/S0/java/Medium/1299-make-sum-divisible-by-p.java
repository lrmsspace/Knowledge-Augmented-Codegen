// Source: https://leetcode.com/problems/make-sum-divisible-by-p/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.
//
// Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
//
// A subarray is defined as a contiguous block of elements in the array.
//
// Example:
// Input: nums = [3,1,4,2], p = 6
// Output: 1
// Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= p <= 109
//

class Solution {
    public int minSubarray(int[] nums, int p) {
        int n = nums.length;
        long total = 0;
        for (int num : nums) {
            total += num;
        }
        long target = total % p;
        if (target == 0) {
            return 0;
        }

        Map<Long, Integer> prefixMap = new HashMap<>();
        prefixMap.put(0L, -1);
        long prefixSum = 0;
        int minLength = n;

        for (int i = 0; i < n; i++) {
            prefixSum = (prefixSum + nums[i]) % p;
            long needed = (prefixSum - target + p) % p;

            if (prefixMap.containsKey(needed)) {
                minLength = Math.min(minLength, i - prefixMap.get(needed));
            }
            prefixMap.put(prefixSum, i);
        }

        return minLength == n ? -1 : minLength;         
    }
}
