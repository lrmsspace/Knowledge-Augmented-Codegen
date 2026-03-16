// Source: https://leetcode.com/problems/maximize-greatness-of-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. You are allowed to permute nums into a new array perm of your choosing.
//
// We define the greatness of nums be the number of indices 0 <= i < nums.length for which perm[i] > nums[i].
//
// Return the maximum possible greatness you can achieve after permuting nums.
//
// Example:
// Input: nums = [1,3,5,2,1,3,1]
// Output: 4
// Explanation: One of the optimal rearrangements is perm = [2,5,1,3,3,1,1].
// At indices = 0, 1, 3, and 4, perm[i] > nums[i]. Hence, we return 4.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//

int maximizeGreatness(int* nums, int numsSize) {
    // Sort the array to facilitate the two-pointer technique
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int greatness = 0;
    int j = 0;

    // Use two pointers to find the maximum number of elements in perm that can be greater than nums
    for (int i = 0; i < numsSize; i++) {
        if (j < numsSize && nums[j] <= nums[i]) {
            j++;
        }
        if (j < numsSize) {
            greatness++;
            j++;
        }
    }

    return greatness;       
}
