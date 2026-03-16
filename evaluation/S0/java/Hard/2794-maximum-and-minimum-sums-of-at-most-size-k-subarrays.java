// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subarrays with at most k elements.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 20
//
// Explanation:
//
// The subarrays of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subarray
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
// 			[2, 3]
// 			2
// 			3
// 			5
// 		
// 		
// 			Final Total
// 			 
// 			 
// 			20
// 		
// 	
//
//
// The output would be 20.
//
// Constraints:
// 1 <= nums.length <= 80000
// 	1 <= k <= nums.length
// 	-106 <= nums[i] <= 106
//

class Solution {
    private long getSum(int[] nums, int k, boolean isMax) {
        Deque<Integer> deque = new ArrayDeque<>();
        long sum = 0;
        int n = nums.length;

        for (int i = 0; i < n; i++) {
            while (!deque.isEmpty() && ((isMax && nums[deque.peekLast()] <= nums[i]) || (!isMax && nums[deque.peekLast()] >= nums[i]))) {
                deque.pollLast();
            }
            deque.offerLast(i);

            if (i >= k) {
                if (deque.peekFirst() == i - k) {
                    deque.pollFirst();
                }
            }

            sum += nums[deque.peekFirst()];
        }
        return sum;
    }
    public long minMaxSubarraySum(int[] nums, int k) {
        return getSum(nums, k, true) + getSum(nums, k, false);          
    }
}
