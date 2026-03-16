// Source: https://leetcode.com/problems/count-partitions-with-even-sum-difference/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums of length n.
//
// A partition is defined as an index i where 0 <= i < n - 1, splitting the array into two non-empty subarrays such that:
//
//
// 	Left subarray contains indices [0, i].
// 	Right subarray contains indices [i + 1, n - 1].
//
//
// Return the number of partitions where the difference between the sum of the left and right subarrays is even.
//
// Example:
// Input: nums = [10,10,3,7,6]
//
// Output: 4
//
// Explanation:
//
// The 4 partitions are:
//
//
// 	[10], [10, 3, 7, 6] with a sum difference of 10 - 26 = -16, which is even.
// 	[10, 10], [3, 7, 6] with a sum difference of 20 - 16 = 4, which is even.
// 	[10, 10, 3], [7, 6] with a sum difference of 23 - 13 = 10, which is even.
// 	[10, 10, 3, 7], [6] with a sum difference of 30 - 6 = 24, which is even.
//
// Constraints:
// 2 <= n == nums.length <= 100
// 	1 <= nums[i] <= 100
//

int countPartitions(int* nums, int numsSize) {
    int count = 0;
    int leftSum = 0;
    int totalSum = 0;

    // Calculate the total sum of the array
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }

    // Iterate through the array to find valid partitions
    for (int i = 0; i < numsSize - 1; i++) {
        leftSum += nums[i];
        int rightSum = totalSum - leftSum;

        // Check if the difference is even
        if ((leftSum - rightSum) % 2 == 0) {
            count++;
        }
    }

    return count;       
}
