// Source: https://leetcode.com/problems/most-frequent-number-following-key-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums. You are also given an integer key, which is present in nums.
//
// For every unique integer target in nums, count the number of times target immediately follows an occurrence of key in nums. In other words, count the number of indices i such that:
//
//
// 	0 <= i <= nums.length - 2,
// 	nums[i] == key and,
// 	nums[i + 1] == target.
//
//
// Return the target with the maximum count. The test cases will be generated such that the target with maximum count is unique.
//
// Example:
// Input: nums = [1,100,200,1,100], key = 1
// Output: 100
// Explanation: For target = 100, there are 2 occurrences at indices 1 and 4 which follow an occurrence of key.
// No other integers follow an occurrence of key, so we return 100.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	The test cases will be generated such that the answer is unique.
//

int mostFrequent(int* nums, int numsSize, int key) {
    int counts[1001] = {0};
    int maxCount = 0;
    int result = -1;

    for (int i = 0; i < numsSize - 1; i++) {
        if (nums[i] == key) {
            int target = nums[i + 1];
            counts[target]++;
            if (counts[target] > maxCount) {
                maxCount = counts[target];
                result = target;
            }
        }
    }

    return result;      
}
