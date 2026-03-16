// Source: https://leetcode.com/problems/frequency-of-the-most-frequent-element/   |   Difficulty: Medium
//
// Problem Description:
// The frequency of an element is the number of times it occurs in an array.
//
// You are given an integer array nums and an integer k. In one operation, you can choose an index of nums and increment the element at that index by 1.
//
// Return the maximum possible frequency of an element after performing at most k operations.
//
// Example:
// Input: nums = [1,2,4], k = 5
// Output: 3
// Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
// 4 has a frequency of 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= k <= 105
//

int maxFrequency(int* nums, int numsSize, int k) {
    // Sort the array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    long left = 0, total = 0, result = 1;

    for (long right = 0; right < numsSize; right++) {
        total += nums[right];

        while ((long)(nums[right]) * (right - left + 1) - total > k) {
            total -= nums[left];
            left++;
        }

        result = fmax(result, right - left + 1);
    }

    return result;      
}
