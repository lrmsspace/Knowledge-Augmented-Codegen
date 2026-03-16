// Source: https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, modify the array in the following way:
//
//
// 	choose an index i and replace nums[i] with -nums[i].
//
//
// You should apply this process exactly k times. You may choose the same index i multiple times.
//
// Return the largest possible sum of the array after modifying it in this way.
//
// Example:
// Input: nums = [4,2,3], k = 1
// Output: 5
// Explanation: Choose index 1 and nums becomes [4,-2,3].
//
// Constraints:
// 1 <= nums.length <= 104
// 	-100 <= nums[i] <= 100
// 	1 <= k <= 104
//

int largestSumAfterKNegations(int* nums, int numsSize, int k) {
    // Sort the array to bring negative numbers to the front
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    // Negate the negative numbers first
    for (int i = 0; i < numsSize && k > 0; i++) {
        if (nums[i] < 0) {
            nums[i] = -nums[i];
            k--;
        }
    }

    // If k is still odd, negate the smallest number
    if (k % 2 == 1) {
        int minIndex = 0;
        for (int i = 1; i < numsSize; i++) {
            if (nums[i] < nums[minIndex]) {
                minIndex = i;
            }
        }
        nums[minIndex] = -nums[minIndex];
    }

    // Calculate the sum of the array
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }

    return sum;     
}
