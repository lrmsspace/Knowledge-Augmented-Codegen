// Source: https://leetcode.com/problems/3sum-closest/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.
//
// Return the sum of the three integers.
//
// You may assume that each input would have exactly one solution.
//
// Example:
// Input: nums = [-1,2,1,-4], target = 1
// Output: 2
// Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
//
// Constraints:
// 3 <= nums.length <= 500
// 	-1000 <= nums[i] <= 1000
// 	-104 <= target <= 104
//

int threeSumClosest(int* nums, int numsSize, int target) {
    // Sort the array to use two-pointer technique
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int closestSum = nums[0] + nums[1] + nums[2]; // Initialize with the first three elements

    for (int i = 0; i < numsSize - 2; i++) {
        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            int currentSum = nums[i] + nums[left] + nums[right];

            // Update closestSum if currentSum is closer to target
            if (abs(currentSum - target) < abs(closestSum - target)) {
                closestSum = currentSum;
            }

            // Move pointers based on comparison with target
            if (currentSum < target) {
                left++;
            } else if (currentSum > target) {
                right--;
            } else {
                // If currentSum equals target, it's the closest possible
                return currentSum;
            }
        }
    }

    return closestSum;      
}
