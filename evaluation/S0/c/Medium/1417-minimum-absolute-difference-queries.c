// Source: https://leetcode.com/problems/minimum-absolute-difference-queries/   |   Difficulty: Medium
//
// Problem Description:
// The minimum absolute difference of an array a is defined as the minimum value of |a[i] - a[j]|, where 0 <= i < j < a.length and a[i] != a[j]. If all elements of a are the same, the minimum absolute difference is -1.
//
//
// 	For example, the minimum absolute difference of the array [5,2,3,7,2] is |2 - 3| = 1. Note that it is not 0 because a[i] and a[j] must be different.
//
//
// You are given an integer array nums and the array queries where queries[i] = [li, ri]. For each query i, compute the minimum absolute difference of the subarray nums[li...ri] containing the elements of nums between the 0-based indices li and ri (inclusive).
//
// Return an array ans where ans[i] is the answer to the ith query.
//
// A subarray is a contiguous sequence of elements in an array.
//
// The value of |x| is defined as:
//
//
// 	x if x >= 0.
// 	-x if x < 0.
//
// Example:
// Input: nums = [1,3,4,8], queries = [[0,1],[1,2],[2,3],[0,3]]
// Output: [2,1,4,1]
// Explanation: The queries are processed as follows:
// - queries[0] = [0,1]: The subarray is [1,3] and the minimum absolute difference is |1-3| = 2.
// - queries[1] = [1,2]: The subarray is [3,4] and the minimum absolute difference is |3-4| = 1.
// - queries[2] = [2,3]: The subarray is [4,8] and the minimum absolute difference is |4-8| = 4.
// - queries[3] = [0,3]: The subarray is [1,3,4,8] and the minimum absolute difference is |3-4| = 1.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 100
// 	1 <= queries.length <= 2 * 104
// 	0 <= li < ri < nums.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minDifference(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int** pre = (int**)malloc((numsSize + 1) * sizeof(int*));
    for (int i = 0; i <= numsSize; ++i) {
        pre[i] = (int*)calloc(101, sizeof(int));
    }
    for (int i = 1; i <= numsSize; ++i) {
        for (int j = 1; j <= 100; ++j) {
            pre[i][j] = pre[i - 1][j];
        }
        pre[i][nums[i - 1]]++;
    }

    int* ans = (int*)malloc(queriesSize * sizeof(int));
    for (int i = 0; i < queriesSize; ++i) {
        int l = queries[i][0] + 1;
        int r = queries[i][1] + 1;
        int prev = -1;
        ans[i] = 101;
        for (int j = 1; j <= 100; ++j) {
            if (pre[r][j] - pre[l - 1][j] > 0) {
                if (prev != -1) {
                    ans[i] = fmin(ans[i], j - prev);
                }
                prev = j;
            }
        }
        if (ans[i] == 101) {
            ans[i] = -1;
        }
    }

    for (int i = 0; i <= numsSize; ++i) {
        free(pre[i]);
    }
    free(pre);

    *returnSize = queriesSize;
    return ans;     
}
