// Source: https://leetcode.com/problems/count-of-smaller-numbers-after-self/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].
//
// Example:
// Input: nums = [5,2,6,1]
// Output: [2,1,1,0]
// Explanation:
// To the right of 5 there are 2 smaller elements (2 and 1).
// To the right of 2 there is only 1 smaller element (1).
// To the right of 6 there is 1 smaller element (1).
// To the right of 1 there is 0 smaller element.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = numsSize;
    if (numsSize <= 0) return NULL;

    int offset = 10000; /* offset negative to non-negative */
    int size = 2 * 10000 + 2; /* total possible values in nums plus one extra */
    int *tree = (int*)calloc(size, sizeof(int));
    if (!tree) return NULL;

    int *result = (int*)malloc(numsSize * sizeof(int));
    if (!result) {
        free(tree);
        return NULL;
    }

    for (int i = numsSize - 1; i >= 0; --i) {
        int rank = nums[i] + offset + 1; /* rank is index in tree */
        int sum = 0;
        for (int j = rank - 1; j > 0; j -= j & -j) {
            sum += tree[j];
        }
        result[i] = sum;
        for (int j = rank; j < size; j += j & -j) {
            tree[j] += 1;
        }
    }

    free(tree);
    return result;      
}
