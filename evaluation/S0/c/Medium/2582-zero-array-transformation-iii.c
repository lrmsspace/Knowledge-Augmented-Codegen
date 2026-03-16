// Source: https://leetcode.com/problems/zero-array-transformation-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri].
//
// Each queries[i] represents the following action on nums:
//
//
// 	Decrement the value at each index in the range [li, ri] in nums by at most 1.
// 	The amount by which the value is decremented can be chosen independently for each index.
//
//
// A Zero Array is an array with all its elements equal to 0.
//
// Return the maximum number of elements that can be removed from queries, such that nums can still be converted to a zero array using the remaining queries. If it is not possible to convert nums to a zero array, return -1.
//
// Example:
// Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
//
// Output: 1
//
// Explanation:
//
// After removing queries[2], nums can still be converted to a zero array.
//
//
// 	Using queries[0], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
// 	Using queries[1], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= li <= ri < nums.length
//

int maxRemoval(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    int maxNum = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }

    int left = 0, right = queriesSize, mid;
    int* diff = (int*)calloc(numsSize + 1, sizeof(int));
    int* prefix = (int*)calloc(numsSize, sizeof(int));

    while (left < right) {
        mid = left + (right - left) / 2;

        memset(diff, 0, (numsSize + 1) * sizeof(int));
        for (int i = mid; i < queriesSize; i++) {
            diff[queries[i][0]]++;
            diff[queries[i][1] + 1]--;
        }

        prefix[0] = diff[0];
        for (int i = 1; i < numsSize; i++) {
            prefix[i] = prefix[i - 1] + diff[i];
        }

        int canFormZeroArray = 1;
        for (int i = 0; i < numsSize; i++) {
            if (prefix[i] < nums[i]) {
                canFormZeroArray = 0;
                break;
            }
        }

        if (canFormZeroArray) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    free(diff);
    free(prefix);

    return left - 1;        
}
