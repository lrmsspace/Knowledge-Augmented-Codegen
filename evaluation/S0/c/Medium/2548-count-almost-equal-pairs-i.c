// Source: https://leetcode.com/problems/count-almost-equal-pairs-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// We call two integers x and y in this problem almost equal if both integers can become equal after performing the following operation at most once:
//
//
// 	Choose either x or y and swap any two digits within the chosen number.
//
//
// Return the number of indices i and j in nums where i < j such that nums[i] and nums[j] are almost equal.
//
// Note that it is allowed for an integer to have leading zeros after performing an operation.
//
// Example:
// Input: nums = [3,12,30,17,21]
//
// Output: 2
//
// Explanation:
//
// The almost equal pairs of elements are:
//
//
// 	3 and 30. By swapping 3 and 0 in 30, you get 3.
// 	12 and 21. By swapping 1 and 2 in 12, you get 21.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 106
//

int countPairs(int* nums, int numsSize) {
    int count = 0;

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            int freq1[10] = {0};
            int freq2[10] = {0};

            int num1 = nums[i];
            int num2 = nums[j];

            while (num1 > 0) {
                freq1[num1 % 10]++;
                num1 /= 10;
            }

            while (num2 > 0) {
                freq2[num2 % 10]++;
                num2 /= 10;
            }

            int diffCount = 0;
            for (int k = 0; k < 10; k++) {
                if (freq1[k] != freq2[k]) {
                    diffCount += abs(freq1[k] - freq2[k]);
                }
            }

            if (diffCount <= 4) {
                count++;
            }
        }
    }

    return count;       
}
