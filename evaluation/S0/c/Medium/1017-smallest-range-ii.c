// Source: https://leetcode.com/problems/smallest-range-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// For each index i where 0 <= i < nums.length, change nums[i] to be either nums[i] + k or nums[i] - k.
//
// The score of nums is the difference between the maximum and minimum elements in nums.
//
// Return the minimum score of nums after changing the values at each index.
//
// Example:
// Input: nums = [1], k = 0
// Output: 0
// Explanation: The score is max(nums) - min(nums) = 1 - 1 = 0.
//
// Constraints:
// 1 <= nums.length <= 104
// 	0 <= nums[i] <= 104
// 	0 <= k <= 104
//

int smallestRangeII(int* nums, int numsSize, int k) {
    // Sort the array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*)) (int (*)(int, int)) [](int a, int b) {
        return a - b;
    });

    int minScore = nums[numsSize - 1] - nums[0]; // Initial score without any changes

    for (int i = 0; i < numsSize - 1; i++) {
        int high = fmax(nums[i] + k, nums[numsSize - 1] - k);
        int low = fmin(nums[0] + k, nums[i + 1] - k);
        minScore = fmin(minScore, high - low);
    }

    return minScore;        
}
