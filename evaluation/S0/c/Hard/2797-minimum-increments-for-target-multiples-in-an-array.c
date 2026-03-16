// Source: https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays, nums and target.
//
// In a single operation, you may increment any element of nums by 1.
//
// Return the minimum number of operations required so that each element in target has at least one multiple in nums.
//
// Example:
// Input: nums = [1,2,3], target = [4]
//
// Output: 1
//
// Explanation:
//
// The minimum number of operations required to satisfy the condition is 1.
//
//
// 	Increment 3 to 4 with just one operation, making 4 a multiple of itself.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= target.length <= 4
// 	target.length <= nums.length
// 	1 <= nums[i], target[i] <= 104
//

int minimumIncrements(int* nums, int numsSize, int* target, int targetSize) {
    int maxTarget = 0;
    for (int i = 0; i < targetSize; ++i) {
        if (target[i] > maxTarget) maxTarget = target[i];
    }

    int *minIncs = (int*)calloc(maxTarget + 1, sizeof(int));
    if (!minIncs) return -1; /* allocation failure */

    for (int i = 0; i < numsSize; ++i) {
        int n = nums[i];
        for (int mult = 1; n * mult <= maxTarget; ++mult) {
            int t = n * mult;
            int incs = n * mult - n;
            if (minIncs[t] == 0 || incs < minIncs[t]) {
                minIncs[t] = incs;
            }
        }
    }

    int totalIncs = 0;
    for (int i = 0; i < targetSize; ++i) {
        int t = target[i];
        if (minIncs[t] == 0) {
            free(minIncs);
            return -1; /* no multiple found */
        }
        totalIncs += minIncs[t];
    }

    free(minIncs);
    return totalIncs;       
}
