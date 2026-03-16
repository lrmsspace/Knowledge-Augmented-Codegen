// Source: https://leetcode.com/problems/delete-and-earn/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You want to maximize the number of points you get by performing the following operation any number of times:
//
//
// 	Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
//
//
// Return the maximum number of points you can earn by applying the above operation some number of times.
//
// Example:
// Input: nums = [3,4,2]
// Output: 6
// Explanation: You can perform the following operations:
// - Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
// - Delete 2 to earn 2 points. nums = [].
// You earn a total of 6 points.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 104
//

int deleteAndEarn(int* nums, int numsSize) {
    int maxVal = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }

    int* points = (int*)calloc(maxVal + 1, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        points[nums[i]] += nums[i];
    }

    int prev1 = 0;
    int prev2 = 0;
    for (int i = 0; i <= maxVal; i++) {
        int current = (prev2 + points[i] > prev1) ? prev2 + points[i] : prev1;
        prev2 = prev1;
        prev1 = current;
    }

    free(points);
    return prev1;       
}
