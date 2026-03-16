// Source: https://leetcode.com/problems/count-number-of-distinct-integers-after-reverse-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// You have to take each integer in the array, reverse its digits, and add it to the end of the array. You should apply this operation to the original integers in nums.
//
// Return the number of distinct integers in the final array.
//
// Example:
// Input: nums = [1,13,10,12,31]
// Output: 6
// Explanation: After including the reverse of each number, the resulting array is [1,13,10,12,31,1,31,1,21,13].
// The reversed integers that were added to the end of the array are underlined. Note that for the integer 10, after reversing it, it becomes 01 which is just 1.
// The number of distinct integers in this array is 6 (The numbers 1, 10, 12, 13, 21, and 31).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

int countDistinctIntegers(int* nums, int numsSize) {
    int maxVal = 1000000; // Given constraint: 1 <= nums[i] <= 10^6
    char seen[maxVal + 1];
    for (int i = 0; i <= maxVal; i++) {
        seen[i] = 0;
    }

    int distinctCount = 0;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];

        // Mark the original number as seen
        if (seen[num] == 0) {
            seen[num] = 1;
            distinctCount++;
        }

        // Reverse the digits of the number
        int reversedNum = 0;
        while (num > 0) {
            reversedNum = reversedNum * 10 + (num % 10);
            num /= 10;
        }

        // Mark the reversed number as seen
        if (seen[reversedNum] == 0) {
            seen[reversedNum] = 1;
            distinctCount++;
        }
    }

    return distinctCount;       
}
