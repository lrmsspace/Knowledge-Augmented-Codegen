// Source: https://leetcode.com/problems/most-frequent-even-element/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the most frequent even element.
//
// If there is a tie, return the smallest one. If there is no such element, return -1.
//
// Example:
// Input: nums = [0,1,2,2,4,4,1]
// Output: 2
// Explanation:
// The even elements are 0, 2, and 4. Of these, 2 and 4 appear the most.
// We return the smallest one, which is 2.
//
// Constraints:
// 1 <= nums.length <= 2000
// 	0 <= nums[i] <= 105
//

int mostFrequentEven(int* nums, int numsSize) {
    int freq[100001] = {0};
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            freq[nums[i]]++;
        }
    }

    int maxFreq = 0;
    int result = -1;
    for (int i = 0; i <= 100000; i += 2) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            result = i;
        }
    }

    return result;      
}
