// Source: https://leetcode.com/problems/kth-largest-element-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the kth largest element in the array.
//
// Note that it is the kth largest element in the sorted order, not the kth distinct element.
//
// Can you solve it without sorting?
//
// Example:
// Input: nums = [3,2,1,5,6,4], k = 2
// Output: 5
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

class Solution {
    public int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        for (int num : nums) {
            minHeap.offer(num);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        return minHeap.peek();
        
    }
}
