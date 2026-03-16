// Source: https://leetcode.com/problems/subsets/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums of unique elements, return all possible subsets (the power set).
//
// The solution set must not contain duplicate subsets. Return the solution in any order.
//
// Example:
// Input: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
//
// Constraints:
// 1 <= nums.length <= 10
// 	-10 <= nums[i] <= 10
// 	All the numbers of nums are unique.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int totalSubsets = 1 << numsSize; // 2^n subsets
    int** result = (int**)malloc(totalSubsets * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalSubsets * sizeof(int));
    
    for (int i = 0; i < totalSubsets; i++) {
        int subsetSize = 0;
        for (int j = 0; j < numsSize; j++) {
            if (i & (1 << j)) {
                subsetSize++;
            }
        }
        
        (*returnColumnSizes)[i] = subsetSize;
        result[i] = (int*)malloc(subsetSize * sizeof(int));
        
        int index = 0;
        for (int j = 0; j < numsSize; j++) {
            if (i & (1 << j)) {
                result[i][index++] = nums[j];
            }
        }
    }
    
    *returnSize = totalSubsets;
    return result;      
}
