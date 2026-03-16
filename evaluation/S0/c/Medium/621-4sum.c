// Source: https://leetcode.com/problems/4sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
//
//
// 	0 <= a, b, c, d < n
// 	a, b, c, and d are distinct.
// 	nums[a] + nums[b] + nums[c] + nums[d] == target
//
//
// You may return the answer in any order.
//
// Example:
// Input: nums = [1,0,-1,0,-2,2], target = 0
// Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
//
// Constraints:
// 1 <= nums.length <= 200
// 	-109 <= nums[i] <= 109
// 	-109 <= target <= 109
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    int **res = NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (numsSize < 4) return res;

    // Sort the array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    for (int i = 0; i < numsSize - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates for the first number
        for (int j = i + 1; j < numsSize - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue; // Skip duplicates for the second number
            int left = j + 1;
            int right = numsSize - 1;
            while (left < right) {
                long sum = (long)nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target) {
                    // Found a quadruplet
                    res = realloc(res, sizeof(int*) * (*returnSize + 1));
                    res[*returnSize] = malloc(sizeof(int) * 4);
                    res[*returnSize][0] = nums[i];
                    res[*returnSize][1] = nums[j];
                    res[*returnSize][2] = nums[left];
                    res[*returnSize][3] = nums[right];
                    (*returnSize)++;
                    *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int) * (*returnSize));
                    (*returnColumnSizes)[*returnSize - 1] = 4;

                    // Skip duplicates for the third number
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    // Skip duplicates for the fourth number
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
    }
    return res;     
}
