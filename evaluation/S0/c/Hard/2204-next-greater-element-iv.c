// Source: https://leetcode.com/problems/next-greater-element-iv/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of non-negative integers nums. For each integer in nums, you must find its respective second greater integer.
//
// The second greater integer of nums[i] is nums[j] such that:
//
//
// 	j > i
// 	nums[j] > nums[i]
// 	There exists exactly one index k such that nums[k] > nums[i] and i < k < j.
//
//
// If there is no such nums[j], the second greater integer is considered to be -1.
//
//
// 	For example, in the array [1, 2, 4, 3], the second greater integer of 1 is 4, 2 is 3, and that of 3 and 4 is -1.
//
//
// Return an integer array answer, where answer[i] is the second greater integer of nums[i].
//
// Example:
// Input: nums = [2,4,0,9,6]
// Output: [9,6,6,-1,-1]
// Explanation:
// 0th index: 4 is the first integer greater than 2, and 9 is the second integer greater than 2, to the right of 2.
// 1st index: 9 is the first, and 6 is the second integer greater than 4, to the right of 4.
// 2nd index: 9 is the first, and 6 is the second integer greater than 0, to the right of 0.
// 3rd index: There is no integer greater than 9 to its right, so the second greater integer is considered to be -1.
// 4th index: There is no integer greater than 6 to its right, so the second greater integer is considered to be -1.
// Thus, we return [9,6,6,-1,-1].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* secondGreaterElement(int* nums, int numsSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = numsSize;
    int *res = (int*)malloc(numsSize * sizeof(int));
    if (!res) return NULL;

    int *stack1 = (int*)malloc(numsSize * sizeof(int));
    int *stack2 = (int*)malloc(numsSize * sizeof(int));
    if (!stack1 || !stack2) {
        free(res); free(stack1); free(stack2);
        return NULL;
    }
    int top1 = -1, top2 = -1;

    for (int i = numsSize - 1; i >= 0; --i) {
        res[i] = -1;

        while (top2 >= 0 && nums[stack2[top2]] <= nums[i]) {
            --top2;
        }
        if (top2 >= 0) {
            res[i] = nums[stack2[top2]];
        }

        while (top1 >= 0 && nums[stack1[top1]] <= nums[i]) {
            int idx = stack1[top1--];
            stack2[++top2] = idx;
        }
        stack1[++top1] = i;
    }

    free(stack1);
    free(stack2);
    return res;     
}
