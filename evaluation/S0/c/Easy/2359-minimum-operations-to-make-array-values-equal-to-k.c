// Source: https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// An integer h is called valid if all values in the array that are strictly greater than h are identical.
//
// For example, if nums = [10, 8, 10, 8], a valid integer is h = 9 because all nums[i] > 9 are equal to 10, but 5 is not a valid integer.
//
// You are allowed to perform the following operation on nums:
//
//
// 	Select an integer h that is valid for the current values in nums.
// 	For each index i where nums[i] > h, set nums[i] to h.
//
//
// Return the minimum number of operations required to make every element in nums equal to k. If it is impossible to make all elements equal to k, return -1.
//
// Example:
// Input: nums = [5,2,5,4,5], k = 2
//
// Output: 2
//
// Explanation:
//
// The operations can be performed in order using valid integers 4 and then 2.
//
// Constraints:
// 1 <= nums.length <= 100 
// 	1 <= nums[i] <= 100
// 	1 <= k <= 100
//

int minOperations(int* nums, int numsSize, int k) {
    int operations = 0;
    int foundGreater = 1;

    while (foundGreater) {
        foundGreater = 0;
        int currentMax = -1;
        int countMax = 0;

        for (int i = 0; i < numsSize; i++) {
            if (nums[i] > k) {
                foundGreater = 1;
                if (nums[i] > currentMax) {
                    currentMax = nums[i];
                    countMax = 1;
                } else if (nums[i] == currentMax) {
                    countMax++;
                }
            }
        }

        if (foundGreater) {
            if (countMax > 1) {
                return -1; // More than one distinct value greater than k
            }
            for (int i = 0; i < numsSize; i++) {
                if (nums[i] == currentMax) {
                    nums[i] = k; // Set to k
                }
            }
            operations++;
        }
    }

    return operations;      
}
