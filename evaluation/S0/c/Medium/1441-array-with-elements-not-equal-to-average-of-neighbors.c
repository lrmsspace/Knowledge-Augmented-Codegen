// Source: https://leetcode.com/problems/array-with-elements-not-equal-to-average-of-neighbors/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of distinct integers. You want to rearrange the elements in the array such that every element in the rearranged array is not equal to the average of its neighbors.
//
// More formally, the rearranged array should have the property such that for every i in the range 1 <= i < nums.length - 1, (nums[i-1] + nums[i+1]) / 2 is not equal to nums[i].
//
// Return any rearrangement of nums that meets the requirements.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: [1,2,4,5,3]
// Explanation:
// When i=1, nums[i] = 2, and the average of its neighbors is (1+4) / 2 = 2.5.
// When i=2, nums[i] = 4, and the average of its neighbors is (2+5) / 2 = 3.5.
// When i=3, nums[i] = 5, and the average of its neighbors is (4+3) / 2 = 3.5.
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rearrangeArray(int* nums, int numsSize, int* returnSize) {
    // Sort the array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    // Create a new array to hold the rearranged elements
    int* rearranged = (int*)malloc(numsSize * sizeof(int));
    int left = 0;
    int right = numsSize - 1;
    int index = 0;

    // Alternate between the smallest and largest remaining elements
    while (left <= right) {
        if (index % 2 == 0) {
            rearranged[index++] = nums[left++];
        } else {
            rearranged[index++] = nums[right--];
        }
    }

    *returnSize = numsSize;
    return rearranged;      
}
