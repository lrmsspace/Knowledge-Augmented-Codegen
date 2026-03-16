// Source: https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The value of this array is defined as the sum of |nums[i] - nums[i + 1]| for all 0 <= i < nums.length - 1.
//
// You are allowed to select any subarray of the given array and reverse it. You can perform this operation only once.
//
// Find maximum possible value of the final array.
//
// Example:
// Input: nums = [2,3,1,5,4]
// Output: 10
// Explanation: By reversing the subarray [3,1,5] the array becomes [2,5,1,3,4] whose value is 10.
//
// Constraints:
// 2 <= nums.length <= 3 * 104
// 	-105 <= nums[i] <= 105
// 	The answer is guaranteed to fit in a 32-bit integer.
//

int maxValueAfterReverse(int* nums, int numsSize) {
    if (numsSize < 2) return 0;

    int originalValue = 0;
    for (int i = 0; i < numsSize - 1; ++i) {
        originalValue += abs(nums[i] - nums[i + 1]);
    }

    int maxGain = 0;

    /* Case 1: Reverse a subarray that includes the first element */
    for (int j = 1; j < numsSize - 1; ++j) {
        int gain = abs(nums[0] - nums[j + 1]) - abs(nums[j] - nums[j + 1]);
        if (gain > maxGain) maxGain = gain;
    }

    /* Case 2: Reverse a subarray that includes the last element */
    for (int i = 1; i < numsSize - 1; ++i) {
        int gain = abs(nums[numsSize - 1] - nums[i - 1]) - abs(nums[i] - nums[i - 1]);
        if (gain > maxGain) maxGain = gain;
    }

    /* Case 3: Reverse a subarray that does not include the first or last element */
    int minPairMax = 100001; // since nums[i] can be as low as -10^5
    int maxPairMin = -100001; // since nums[i] can be as high as 10^5

    for (int i = 0; i < numsSize - 1; ++i) {
        int a = nums[i];
        int b = nums[i + 1];
        if (a > b) {
            if (b > maxPairMin) maxPairMin = b;
        } else {
            if (a < minPairMax) minPairMax = a;
        }
    }

    int gain = 2 * (maxPairMin - minPairMax);
    if (gain > maxGain) maxGain = gain;

    return originalValue + maxGain;     
}
