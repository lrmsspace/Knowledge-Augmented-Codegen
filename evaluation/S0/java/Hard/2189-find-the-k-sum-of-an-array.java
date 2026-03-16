// Source: https://leetcode.com/problems/find-the-k-sum-of-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. You can choose any subsequence of the array and sum all of its elements together.
//
// We define the K-Sum of the array as the kth largest subsequence sum that can be obtained (not necessarily distinct).
//
// Return the K-Sum of the array.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Note that the empty subsequence is considered to have a sum of 0.
//
// Example:
// Input: nums = [2,4,-2], k = 5
// Output: 2
// Explanation: All the possible subsequence sums that we can obtain are the following sorted in decreasing order:
// 6, 4, 4, 2, 2, 0, 0, -2.
// The 5-Sum of the array is 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= k <= min(2000, 2n)
//

class Solution {
    public long kSum(int[] nums, int k) {
        PriorityQueue<Long> minHeap = new PriorityQueue<>();
        minHeap.offer(0L);

        for (int num : nums) {
            if (num <= 0) continue;

            int size = minHeap.size();
            for (int i = 0; i < size; i++) {
                long currentSum = minHeap.poll();

                long newSum = currentSum + num;
                minHeap.offer(currentSum);

                if (minHeap.size() < k) {
                    minHeap.offer(newSum);
                } else if (newSum > minHeap.peek()) {
                    minHeap.offer(newSum);
                    minHeap.poll();
                } else {
                    break;
                }
            }
        }

        return minHeap.peek();          
    }
}
