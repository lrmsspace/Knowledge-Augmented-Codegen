// Source: https://leetcode.com/problems/apply-operations-to-make-all-array-elements-equal-to-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and a positive integer k.
//
// You can apply the following operation on the array any number of times:
//
//
// 	Choose any subarray of size k from the array and decrease all its elements by 1.
//
//
// Return true if you can make all the array elements equal to 0, or false otherwise.
//
// A subarray is a contiguous non-empty part of an array.
//
// Example:
// Input: nums = [2,2,3,1,1,0], k = 3
// Output: true
// Explanation: We can do the following operations:
// - Choose the subarray [2,2,3]. The resulting array will be nums = [1,1,2,1,1,0].
// - Choose the subarray [2,1,1]. The resulting array will be nums = [1,1,1,0,0,0].
// - Choose the subarray [1,1,1]. The resulting array will be nums = [0,0,0,0,0,0].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	0 <= nums[i] <= 106
//

bool checkArray(int* nums, int numsSize, int k) {
    int* diff = (int*)calloc(numsSize + 1, sizeof(int));
    int currDec = 0;

    for (int i = 0; i < numsSize; i++) {
        currDec += diff[i];
        int requiredDec = nums[i] - currDec;

        if (requiredDec < 0) {
            free(diff);
            return false;
        }

        if (requiredDec > 0) {
            if (i + k > numsSize) {
                free(diff);
                return false;
            }
            currDec += requiredDec;
            diff[i + k] -= requiredDec;
        }
    }

    free(diff);
    return true;        
}
