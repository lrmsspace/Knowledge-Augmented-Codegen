// Source: https://leetcode.com/problems/set-mismatch/   |   Difficulty: Easy
//
// Problem Description:
// You have a set of integers s, which originally contains all the numbers from 1 to n. Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set, which results in repetition of one number and loss of another number.
//
// You are given an integer array nums representing the data status of this set after the error.
//
// Find the number that occurs twice and the number that is missing and return them in the form of an array.
//
// Example:
// Input: nums = [1,2,2,4]
// Output: [2,3]
//
// Constraints:
// 2 <= nums.length <= 104
// 	1 <= nums[i] <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    int* count = (int*)calloc(numsSize + 1, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }
    for (int i = 1; i <= numsSize; i++) {
        if (count[i] == 2) {
            result[0] = i; // duplicated number
        } else if (count[i] == 0) {
            result[1] = i; // missing number
        }
    }
    free(count);
    *returnSize = 2;
    return result;      
}
