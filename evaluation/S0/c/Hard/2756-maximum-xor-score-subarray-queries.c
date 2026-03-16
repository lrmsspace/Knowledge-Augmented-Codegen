// Source: https://leetcode.com/problems/maximum-xor-score-subarray-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers, and a 2D integer array queries of size q, where queries[i] = [li, ri].
//
// For each query, you must find the maximum XOR score of any subarray of nums[li..ri].
//
// The XOR score of an array a is found by repeatedly applying the following operations on a so that only one element remains, that is the score:
//
//
// 	Simultaneously replace a[i] with a[i] XOR a[i + 1] for all indices i except the last one.
// 	Remove the last element of a.
//
//
// Return an array answer of size q where answer[i] is the answer to query i.
//
// Example:
// Input: nums = [2,8,4,32,16,1], queries = [[0,2],[1,4],[0,5]]
//
// Output: [12,60,60]
//
// Explanation:
//
// In the first query, nums[0..2] has 6 subarrays [2], [8], [4], [2, 8], [8, 4], and [2, 8, 4] each with a respective XOR score of 2, 8, 4, 10, 12, and 6. The answer for the query is 12, the largest of all XOR scores.
//
// In the second query, the subarray of nums[1..4] with the largest XOR score is nums[1..4] with a score of 60.
//
// In the third query, the subarray of nums[0..5] with the largest XOR score is nums[1..4] with a score of 60.
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	0 <= nums[i] <= 231 - 1
// 	1 <= q == queries.length <= 105
// 	queries[i].length == 2 
// 	queries[i] = [li, ri]
// 	0 <= li <= ri <= n - 1
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumSubarrayXor(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    if (queriesSize <= 0) return NULL;

    /* Precompute prefix XORs */
    int prefixXor[numsSize + 1];
    prefixXor[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefixXor[i + 1] = prefixXor[i] ^ nums[i];
    }

    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;

    for (int q = 0; q < queriesSize; ++q) {
        int li = queries[q][0];
        int ri = queries[q][1];
        int maxXor = 0;

        /* Check all subarrays within nums[li..ri] */
        for (int start = li; start <= ri; ++start) {
            for (int end = start; end <= ri; ++end) {
                int subarrayXor = prefixXor[end + 1] ^ prefixXor[start];
                if (subarrayXor > maxXor) {
                    maxXor = subarrayXor;
                }
            }
        }
        results[q] = maxXor;
    }

    return results;     
}
