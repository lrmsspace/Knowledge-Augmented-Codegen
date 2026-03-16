// Source: https://leetcode.com/problems/jump-game-vi/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// You are initially standing at index 0. In one move, you can jump at most k steps forward without going outside the boundaries of the array. That is, you can jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.
//
// You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j] for each index j you visited in the array.
//
// Return the maximum score you can get.
//
// Example:
// Input: nums = [1,-1,-2,4,-7,3], k = 2
// Output: 7
// Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.
//
// Constraints:
// 1 <= nums.length, k <= 105
// 	-104 <= nums[i] <= 104
//

int maxResult(int* nums, int numsSize, int k) {
    int n = numsSize;
    int* dp = (int*)malloc(n * sizeof(int));
    dp[0] = nums[0];

    // Deque to store indices of the dp array
    int* deque = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;
    deque[back++] = 0;

    for (int i = 1; i < n; i++) {
        // Remove indices that are out of the current window
        while (front < back && deque[front] < i - k) {
            front++;
        }

        // The maximum score to reach index i
        dp[i] = dp[deque[front]] + nums[i];

        // Maintain the deque in decreasing order of dp values
        while (front < back && dp[deque[back - 1]] <= dp[i]) {
            back--;
        }
        deque[back++] = i;
    }

    int result = dp[n - 1];
    free(dp);
    free(deque);
    return result;      
}
