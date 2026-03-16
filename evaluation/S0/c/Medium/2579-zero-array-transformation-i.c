// Source: https://leetcode.com/problems/zero-array-transformation-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri].
//
// For each queries[i]:
//
//
// 	Select a subset of indices within the range [li, ri] in nums.
// 	Decrement the values at the selected indices by 1.
//
//
// A Zero Array is an array where all elements are equal to 0.
//
// Return true if it is possible to transform nums into a Zero Array after processing all the queries sequentially, otherwise return false.
//
// Example:
// Input: nums = [1,0,1], queries = [[0,2]]
//
// Output: true
//
// Explanation:
//
//
// 	For i = 0:
//
// 	
// 		Select the subset of indices as [0, 2] and decrement the values at these indices by 1.
// 		The array will become [0, 0, 0], which is a Zero Array.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= li <= ri < nums.length
//

bool isZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    int *diff = (int *)calloc(numsSize + 1, sizeof(int));
    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        diff[l] += 1;
        diff[r + 1] -= 1;
    }
    int curr = 0;
    for (int i = 0; i < numsSize; i++) {
        curr += diff[i];
        if (curr > nums[i]) {
            free(diff);
            return false;
        }
    }
    free(diff);
    return true;        
}
