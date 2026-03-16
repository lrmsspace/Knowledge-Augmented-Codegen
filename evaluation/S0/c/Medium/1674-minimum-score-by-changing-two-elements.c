// Source: https://leetcode.com/problems/minimum-score-by-changing-two-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
//
// 	The low score of nums is the minimum absolute difference between any two integers.
// 	The high score of nums is the maximum absolute difference between any two integers.
// 	The score of nums is the sum of the high and low scores.
//
//
// Return the minimum score after changing two elements of nums.
//
// Example:
// Input: nums = [1,4,7,8,5]
//
// Output: 3
//
// Explanation:
//
//
// 	Change nums[0] and nums[1] to be 6 so that nums becomes [6,6,7,8,5].
// 	The low score is the minimum absolute difference: |6 - 6| = 0.
// 	The high score is the maximum absolute difference: |8 - 5| = 3.
// 	The sum of high and low score is 3.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

int minimizeSum(int* nums, int numsSize) {
    // Sort the array to easily access the smallest and largest elements
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    // Initialize the minimum score to a large value
    int minScore = INT_MAX;

    // Consider all possible ways to change two elements
    for (int i = 0; i <= 2; i++) {
        // Calculate the high score after changing two elements
        int highScore = nums[numsSize - 1 - (2 - i)] - nums[i];
        // The low score can be 0 since we can make two elements equal
        int lowScore = 0;
        // Update the minimum score
        minScore = fmin(minScore, highScore + lowScore);
    }

    return minScore;        
}
