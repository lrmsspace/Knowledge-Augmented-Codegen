// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. In one operation, you can replace any element in nums with any integer.
//
// nums is considered continuous if both of the following conditions are fulfilled:
//
//
// 	All elements in nums are unique.
// 	The difference between the maximum element and the minimum element in nums equals nums.length - 1.
//
//
// For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.
//
// Return the minimum number of operations to make nums continuous.
//
// Example:
// Input: nums = [4,2,5,3]
// Output: 0
// Explanation: nums is already continuous.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

int minOperations(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;

    /* remove duplicates by sorting and unique */
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*)) (int (*)(int, int)) ( (int cmp(int a, int b) { return (a > b) - (a < b); })));

    int uniqueSize = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] != nums[i - 1]) {
            nums[uniqueSize++] = nums[i];
        }
    }

    int minOps = numsSize; /* worst case: change all elements */
    int left = 0;
    for (int right = 0; right < uniqueSize; ++right) {
        while (nums[right] - nums[left] >= numsSize) {
            left++;
        }
        int windowSize = right - left + 1;
        int ops = numsSize - windowSize;
        if (ops < minOps) {
            minOps = ops;
        }
    }

    return minOps;      
}
