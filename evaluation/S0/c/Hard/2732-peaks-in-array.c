// Source: https://leetcode.com/problems/peaks-in-array/   |   Difficulty: Hard
//
// Problem Description:
// A peak in an array arr is an element that is greater than its previous and next element in arr.
//
// You are given an integer array nums and a 2D integer array queries.
//
// You have to process queries of two types:
//
//
// 	queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
// 	queries[i] = [2, indexi, vali], change nums[indexi] to vali.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
//
// Output: [0]
//
// Explanation:
//
// First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
//
// Second query: The number of peaks in the [3,1,4,4,5] is 0.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i][0] == 1 or queries[i][0] == 2
// 	For all i that:
// 	
// 		queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
// 		queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countOfPeaks(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize || !queries || queriesSize <= 0 || !queriesColSize) return NULL;
    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;
    *returnSize = 0;

    int *isPeak = (int*)calloc(numsSize, sizeof(int));
    if (!isPeak) {
        free(results);
        return NULL;
    }

    for (int i = 1; i < numsSize - 1; ++i) {
        if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
            isPeak[i] = 1;
        }
    }

    for (int q = 0; q < queriesSize; ++q) {
        int type = queries[q][0];
        if (type == 1) {
            int li = queries[q][1];
            int ri = queries[q][2];
            int count = 0;
            for (int i = li + 1; i < ri; ++i) {
                count += isPeak[i];
            }
            results[(*returnSize)++] = count;
        } else if (type == 2) {
            int index = queries[q][1];
            int val = queries[q][2];
            nums[index] = val;

            for (int i = index - 1; i <= index + 1; ++i) {
                if (i > 0 && i < numsSize - 1) {
                    isPeak[i] = (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) ? 1 : 0;
                }
            }
        }
    }

    free(isPeak);
    return results;     
}
