// Source: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums consisting of 3 * n elements.
//
// You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:
//
//
// 	The first n elements belonging to the first part and their sum is sumfirst.
// 	The next n elements belonging to the second part and their sum is sumsecond.
//
//
// The difference in sums of the two parts is denoted as sumfirst - sumsecond.
//
//
// 	For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
// 	Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
//
//
// Return the minimum difference possible between the sums of the two parts after the removal of n elements.
//
// Example:
// Input: nums = [3,1,2]
// Output: -1
// Explanation: Here, nums has 3 elements, so n = 1. 
// Thus we have to remove 1 element from nums and divide the array into two equal parts.
// - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
// - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
// - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
// The minimum difference between sums of the two parts is min(-1,1,2) = -1.
//
// Constraints:
// nums.length == 3 * n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
    public long minimumDifference(int[] nums) {
        int n = nums.length / 3;

        long[] leftMin = new long[n + 1];
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        long leftSum = 0;
        for (int i = 0; i < 2 * n; i++) {
            leftSum += nums[i];
            maxHeap.offer(nums[i]);
            if (maxHeap.size() > n) {
                leftSum -= maxHeap.poll();
            }
            if (maxHeap.size() == n) {
                leftMin[i - n + 1] = leftSum;
            }
        }

        long[] rightMax = new long[n + 1];
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        long rightSum = 0;
        for (int i = nums.length - 1; i >= n; i--) {
            rightSum += nums[i];
            minHeap.offer(nums[i]);
            if (minHeap.size() > n) {
                rightSum -= minHeap.poll();
            }
            if (minHeap.size() == n) {
                rightMax[i - n] = rightSum;
            }
        }

        long minDiff = Long.MAX_VALUE;
        for (int i = 0; i <= n; i++) {
            minDiff = Math.min(minDiff, leftMin[i] - rightMax[i]);
        }

        return minDiff;         
    }
}
