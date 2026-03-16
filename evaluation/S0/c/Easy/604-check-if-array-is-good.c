// Source: https://leetcode.com/problems/check-if-array-is-good/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. We consider an array good if it is a permutation of an array base[n].
//
// base[n] = [1, 2, ..., n - 1, n, n] (in other words, it is an array of length n + 1 which contains 1 to n - 1 exactly once, plus two occurrences of n). For example, base[1] = [1, 1] and base[3] = [1, 2, 3, 3].
//
// Return true if the given array is good, otherwise return false.
//
// Note: A permutation of integers represents an arrangement of these numbers.
//
// Example:
// Input: nums = [2, 1, 3]
// Output: false
// Explanation: Since the maximum element of the array is 3, the only candidate n for which this array could be a permutation of base[n], is n = 3. However, base[3] has four elements but array nums has three. Therefore, it can not be a permutation of base[3] = [1, 2, 3, 3]. So the answer is false.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= num[i] <= 200
//

bool isGood(int* nums, int numsSize) {
    int max = 0;
    int countMax = 0;
    int *seen = (int *)calloc(numsSize + 1, sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
            countMax = 1;
        } else if (nums[i] == max) {
            countMax++;
        }

        if (nums[i] > numsSize || seen[nums[i]] == 1) {
            free(seen);
            return false;
        }
        seen[nums[i]] = 1;
    }

    free(seen);
    return (max == numsSize - 1 && countMax == 2);      
}
