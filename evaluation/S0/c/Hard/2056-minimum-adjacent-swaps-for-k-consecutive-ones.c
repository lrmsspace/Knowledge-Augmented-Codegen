// Source: https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.
//
// Return the minimum number of moves required so that nums has k consecutive 1's.
//
// Example:
// Input: nums = [1,0,0,1,0,1], k = 2
// Output: 1
// Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is 0 or 1.
// 	1 <= k <= sum(nums)
//

int minMoves(int* nums, int numsSize, int k) {
    int onesCount = 0;
    int *positions = (int*)malloc(numsSize * sizeof(int));
    if (!positions) return -1; /* allocation failure */

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            positions[onesCount++] = i;
        }
    }

    int64_t prefixSum[onesCount + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < onesCount; ++i) {
        prefixSum[i + 1] = prefixSum[i] + positions[i];
    }

    int64_t minMoves = INT64_MAX;
    for (int i = 0; i <= onesCount - k; ++i) {
        int mid = i + k / 2;
        int64_t leftCost = (int64_t)positions[mid] * (mid - i) - (prefixSum[mid] - prefixSum[i]);
        int64_t rightCost = (prefixSum[i + k] - prefixSum[mid + 1]) - (int64_t)positions[mid] * (i + k - mid - 1);
        int64_t totalCost = leftCost + rightCost;

        /* Adjust for the triangular number offset */
        int halfK = k / 2;
        int64_t offset = (int64_t)halfK * (halfK + (k % 2 == 0 ? -1 : 0));
        totalCost -= offset;

        if (totalCost < minMoves) {
            minMoves = totalCost;
        }
    }

    free(positions);
    return (int)minMoves;       
}
