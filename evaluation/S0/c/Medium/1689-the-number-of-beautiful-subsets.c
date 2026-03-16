// Source: https://leetcode.com/problems/the-number-of-beautiful-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of positive integers and a positive integer k.
//
// A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.
//
// Return the number of non-empty beautiful subsets of the array nums.
//
// A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [2,4,6], k = 2
// Output: 4
// Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
// It can be proved that there are only 4 beautiful subsets in the array [2,4,6].
//
// Constraints:
// 1 <= nums.length <= 18
// 	1 <= nums[i], k <= 1000
//

int beautifulSubsets(int* nums, int numsSize, int k) {
    int count = 0;
    int total = 1 << numsSize; // Total number of subsets

    for (int mask = 1; mask < total; mask++) { // Start from 1 to avoid empty subset
        int isBeautiful = 1; // Assume the subset is beautiful
        for (int i = 0; i < numsSize; i++) {
            if (mask & (1 << i)) { // If nums[i] is included in the subset
                for (int j = i + 1; j < numsSize; j++) {
                    if (mask & (1 << j)) { // If nums[j] is also included in the subset
                        if (abs(nums[i] - nums[j]) == k) {
                            isBeautiful = 0; // Found a pair with absolute difference k
                            break;
                        }
                    }
                }
            }
            if (!isBeautiful) break; // No need to check further if already not beautiful
        }
        if (isBeautiful) count++; // Increment count if the subset is beautiful
    }

    return count;       
}
