// Source: https://leetcode.com/problems/summary-ranges/   |   Difficulty: Easy
//
// Problem Description:
// You are given a sorted unique integer array nums.
//
// A range [a,b] is the set of all integers from a to b (inclusive).
//
// Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That is, each element of nums is covered by exactly one of the ranges, and there is no integer x such that x is in one of the ranges but not in nums.
//
// Each range [a,b] in the list should be output as:
//
//
// 	"a->b" if a != b
// 	"a" if a == b
//
// Example:
// Input: nums = [0,1,2,4,5,7]
// Output: ["0->2","4->5","7"]
// Explanation: The ranges are:
// [0,2] --> "0->2"
// [4,5] --> "4->5"
// [7,7] --> "7"
//
// Constraints:
// 0 <= nums.length <= 20
// 	-231 <= nums[i] <= 231 - 1
// 	All the values of nums are unique.
// 	nums is sorted in ascending order.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** summaryRanges(int* nums, int numsSize, int* returnSize) {
    char** result = (char**)malloc(numsSize * sizeof(char*));
    *returnSize = 0;
    if (numsSize == 0) {
        return result;
    }

    int start = nums[0];
    int end = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == end + 1) {
            end = nums[i];
        } else {
            result[*returnSize] = (char*)malloc(25 * sizeof(char));
            if (start == end) {
                sprintf(result[*returnSize], "%d", start);
            } else {
                sprintf(result[*returnSize], "%d->%d", start, end);
            }
            (*returnSize)++;
            start = nums[i];
            end = nums[i];
        }
    }

    result[*returnSize] = (char*)malloc(25 * sizeof(char));
    if (start == end) {
        sprintf(result[*returnSize], "%d", start);
    } else {
        sprintf(result[*returnSize], "%d->%d", start, end);
    }
    (*returnSize)++;

    return result;      
}
