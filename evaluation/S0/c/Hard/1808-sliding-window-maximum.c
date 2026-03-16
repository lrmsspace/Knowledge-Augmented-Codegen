// Source: https://leetcode.com/problems/sliding-window-maximum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
//
// Return the max sliding window.
//
// Example:
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [3,3,5,5,6,7]
// Explanation: 
// Window position                Max
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	1 <= k <= nums.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (!returnSize || numsSize <= 0 || k <= 0 || k > numsSize) {
        if (returnSize) *returnSize = 0;
        return NULL;
    }

    int resSize = numsSize - k + 1;
    int *results = (int*)malloc(resSize * sizeof(int));
    if (!results) {
        *returnSize = 0;
        return NULL;
    }

    int *deque = (int*)malloc(numsSize * sizeof(int));
    if (!deque) {
        free(results);
        *returnSize = 0;
        return NULL;
    }
    int front = 0, back = 0;

    for (int i = 0; i < numsSize; ++i) {
        while (front < back && deque[front] <= i - k) {
            front++;
        }
        while (front < back && nums[deque[back - 1]] < nums[i]) {
            back--;
        }
        deque[back++] = i;
        if (i >= k - 1) {
            results[i - k + 1] = nums[deque[front]];
        }
    }

    free(deque);
    *returnSize = resSize;
    return results;     
}
