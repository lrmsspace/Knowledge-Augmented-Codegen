// Source: https://leetcode.com/problems/number-of-squareful-arrays/   |   Difficulty: Hard
//
// Problem Description:
// An array is squareful if the sum of every pair of adjacent elements is a perfect square.
//
// Given an integer array nums, return the number of permutations of nums that are squareful.
//
// Two permutations perm1 and perm2 are different if there is some index i such that perm1[i] != perm2[i].
//
// Example:
// Input: nums = [1,17,8]
// Output: 2
// Explanation: [1,8,17] and [17,8,1] are the valid permutations.
//
// Constraints:
// 1 <= nums.length <= 12
// 	0 <= nums[i] <= 109
//

int numSquarefulPerms(int* nums, int numsSize) {
    int count = 0;
    int used[numsSize];
    for (int i = 0; i < numsSize; i++) used[i] = 0;

    int isPerfectSquare(int x) {
        int s = (int)(sqrt(x) + 0.5);
        return s * s == x;
    }

    void backtrack(int pathLen) {
        if (pathLen == numsSize) {
            count++;
            return;
        }
        for (int i = 0; i < numsSize; i++) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
            if (pathLen > 0) {
                int lastNum = -1;
                for (int j = 0; j < numsSize; j++) {
                    if (used[j]) lastNum = nums[j];
                }
                if (!isPerfectSquare(lastNum + nums[i])) continue;
            }
            used[i] = 1;
            backtrack(pathLen + 1);
            used[i] = 0;
        }
    }

    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    backtrack(0);
    return count;
}
