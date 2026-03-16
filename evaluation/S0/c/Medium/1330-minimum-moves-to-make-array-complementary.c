// Source: https://leetcode.com/problems/minimum-moves-to-make-array-complementary/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.
//
// The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number. For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.
//
// Return the minimum number of moves required to make nums complementary.
//
// Example:
// Input: nums = [1,2,4,3], limit = 4
// Output: 1
// Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
// nums[0] + nums[3] = 1 + 3 = 4.
// nums[1] + nums[2] = 2 + 2 = 4.
// nums[2] + nums[1] = 2 + 2 = 4.
// nums[3] + nums[0] = 3 + 1 = 4.
// Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	1 <= nums[i] <= limit <= 105
// 	n is even.
//

int minMoves(int* nums, int numsSize, int limit) {
    int n = numsSize;
    int size = 2 * limit + 2;
    int* prefixSum = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < n / 2; i++) {
        int a = nums[i];
        int b = nums[n - 1 - i];
        int low = (a < b ? a : b) + 1;
        int high = (a > b ? a : b) + limit + 1;
        int sum = a + b;

        prefixSum[2] += 2;               // Default: 2 moves for all sums
        prefixSum[low] -= 1;            // From 'low' sum, only 1 move needed
        prefixSum[sum] -= 1;            // At 'sum', 0 moves needed
        prefixSum[sum + 1] += 1;        // After 'sum', back to 1 move needed
        prefixSum[high] += 1;           // From 'high' sum onwards, back to 2 moves needed
    }

    int minMoves = n; // Maximum possible moves is n
    int currentMoves = 0;
    for (int s = 2; s < size; s++) {
        currentMoves += prefixSum[s];
        if (currentMoves < minMoves) {
            minMoves = currentMoves;
        }
    }

    free(prefixSum);
    return minMoves;        
}
