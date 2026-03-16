// Source: https://leetcode.com/problems/minimum-sum-of-mountain-triplets-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of integers.
//
// A triplet of indices (i, j, k) is a mountain if:
//
//
// 	i < j < k
// 	nums[i] < nums[j] and nums[k] < nums[j]
//
//
// Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return -1.
//
// Example:
// Input: nums = [8,6,1,5,3]
// Output: 9
// Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
// - 2 < 3 < 4
// - nums[2] < nums[3] and nums[4] < nums[3]
// And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 108
//

int minimumSum(int* nums, int numsSize) {
    int n = numsSize;
    int* leftMin = (int*)malloc(n * sizeof(int));
    int* rightMin = (int*)malloc(n * sizeof(int));
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;

    // Find the minimum element to the left of each element
    for (int i = 0; i < n; i++) {
        while (top >= 0 && stack[top] >= nums[i]) {
            top--;
        }
        leftMin[i] = (top >= 0) ? stack[top] : INT_MAX;
        stack[++top] = nums[i];
    }

    // Reset stack for right side processing
    top = -1;

    // Find the minimum element to the right of each element
    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && stack[top] >= nums[i]) {
            top--;
        }
        rightMin[i] = (top >= 0) ? stack[top] : INT_MAX;
        stack[++top] = nums[i];
    }

    int minSum = INT_MAX;

    // Calculate the minimum sum of mountain triplets
    for (int i = 0; i < n; i++) {
        if (leftMin[i] != INT_MAX && rightMin[i] != INT_MAX) {
            int currentSum = leftMin[i] + nums[i] + rightMin[i];
            if (currentSum < minSum) {
                minSum = currentSum;
            }
        }
    }

    free(leftMin);
    free(rightMin);
    free(stack);

    return (minSum == INT_MAX) ? -1 : minSum;       
}
