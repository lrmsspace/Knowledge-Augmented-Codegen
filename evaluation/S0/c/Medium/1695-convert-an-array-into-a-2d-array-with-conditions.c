// Source: https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You need to create a 2D array from nums satisfying the following conditions:
//
//
// 	The 2D array should contain only the elements of the array nums.
// 	Each row in the 2D array contains distinct integers.
// 	The number of rows in the 2D array should be minimal.
//
//
// Return the resulting array. If there are multiple answers, return any of them.
//
// Note that the 2D array can have a different number of elements on each row.
//
// Example:
// Input: nums = [1,3,4,1,2,3,1]
// Output: [[1,3,4,2],[1,3],[1]]
// Explanation: We can create a 2D array that contains the following rows:
// - 1,3,4,2
// - 1,3
// - 1
// All elements of nums were used, and each row of the 2D array contains distinct integers, so it is a valid answer.
// It can be shown that we cannot have less than 3 rows in a valid array.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= nums.length
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findMatrix(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int freq[201] = {0};
    int maxFreq = 0;
    
    // Count frequency of each number and find the maximum frequency
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
        if (freq[nums[i]] > maxFreq) {
            maxFreq = freq[nums[i]];
        }
    }
    
    // Allocate memory for the result 2D array
    int** result = (int**)malloc(maxFreq * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxFreq * sizeof(int));
    
    // Initialize each row in the result array
    for (int i = 0; i < maxFreq; i++) {
        result[i] = (int*)malloc(numsSize * sizeof(int));
        (*returnColumnSizes)[i] = 0; // Initialize column size for each row
    }
    
    // Fill the result array
    for (int num = 1; num <= 200; num++) {
        while (freq[num] > 0) {
            for (int row = 0; row < maxFreq; row++) {
                if (freq[num] > 0) {
                    result[row][(*returnColumnSizes)[row]++] = num;
                    freq[num]--;
                } else {
                    break;
                }
            }
        }
    }
    
    *returnSize = maxFreq;
    return result;      
}
