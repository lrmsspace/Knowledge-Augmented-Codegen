// Source: https://leetcode.com/problems/longest-square-streak-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. A subsequence of nums is called a square streak if:
//
//
// 	The length of the subsequence is at least 2, and
// 	after sorting the subsequence, each element (except the first element) is the square of the previous number.
//
//
// Return the length of the longest square streak in nums, or return -1 if there is no square streak.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [4,3,6,16,8,2]
// Output: 3
// Explanation: Choose the subsequence [4,16,2]. After sorting it, it becomes [2,4,16].
// - 4 = 2 * 2.
// - 16 = 4 * 4.
// Therefore, [4,16,2] is a square streak.
// It can be shown that every subsequence of length 4 is not a square streak.
//
// Constraints:
// 2 <= nums.length <= 105
// 	2 <= nums[i] <= 105
//

int longestSquareStreak(int* nums, int numsSize) {
    #define MAX_NUM 100000
    #define HASH_SIZE (MAX_NUM + 1)

    // Create a hash table to mark the presence of numbers in nums
    bool hash[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        hash[i] = false;
    }
    for (int i = 0; i < numsSize; i++) {
        hash[nums[i]] = true;
    }

    int longest_streak = -1;

    // Iterate through each number in nums
    for (int i = 0; i < numsSize; i++) {
        int current_num = nums[i];
        int current_streak = 0;

        // Check for square streak starting from current_num
        while (current_num <= MAX_NUM && hash[current_num]) {
            current_streak++;
            long long next_num = (long long)current_num * current_num;
            if (next_num > MAX_NUM) {
                break;
            }
            current_num = (int)next_num;
        }

        // Update longest streak if current streak is valid and longer
        if (current_streak >= 2 && current_streak > longest_streak) {
            longest_streak = current_streak;
        }
    }

    return longest_streak;      
}
