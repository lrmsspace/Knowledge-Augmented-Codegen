// Source: https://leetcode.com/problems/recover-the-original-array/   |   Difficulty: Hard
//
// Problem Description:
// Alice had a 0-indexed array arr consisting of n positive integers. She chose an arbitrary positive integer k and created two new 0-indexed integer arrays lower and higher in the following manner:
//
//
// 	lower[i] = arr[i] - k, for every index i where 0 <= i < n
// 	higher[i] = arr[i] + k, for every index i where 0 <= i < n
//
//
// Unfortunately, Alice lost all three arrays. However, she remembers the integers that were present in the arrays lower and higher, but not the array each integer belonged to. Help Alice and recover the original array.
//
// Given an array nums consisting of 2n integers, where exactly n of the integers were present in lower and the remaining in higher, return the original array arr. In case the answer is not unique, return any valid array.
//
// Note: The test cases are generated such that there exists at least one valid array arr.
//
// Example:
// Input: nums = [2,10,6,4,8,12]
// Output: [3,7,11]
// Explanation:
// If arr = [3,7,11] and k = 1, we get lower = [2,6,10] and higher = [4,8,12].
// Combining lower and higher gives us [2,6,10,4,8,12], which is a permutation of nums.
// Another valid possibility is that arr = [5,7,9] and k = 3. In that case, lower = [2,4,6] and higher = [8,10,12].
//
// Constraints:
// 2 * n == nums.length
// 	1 <= n <= 1000
// 	1 <= nums[i] <= 109
// 	The test cases are generated such that there exists at least one valid array arr.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* recoverArray(int* nums, int numsSize, int* returnSize) {
    if (!returnSize || numsSize % 2 != 0 || numsSize < 2) return NULL;

    int n = numsSize / 2;
    int *res = (int*)malloc(n * sizeof(int));
    if (!res) return NULL;

    // Sort the input array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    // Try all possible k values
    for (int i = 1; i < numsSize; ++i) {
        int k = nums[i] - nums[0];
        if (k <= 0 || k % 2 != 0) continue;
        k /= 2;

        int *used = (int*)calloc(numsSize, sizeof(int));
        if (!used) {
            free(res);
            return NULL;
        }

        int idx = 0;
        for (int j = 0; j < numsSize; ++j) {
            if (used[j]) continue;
            used[j] = 1;
            int target = nums[j] + 2 * k;
            int found = 0;
            for (int m = 0; m < numsSize; ++m) {
                if (!used[m] && nums[m] == target) {
                    used[m] = 1;
                    res[idx++] = nums[j] + k;
                    found = 1;
                    break;
                }
            }
            if (!found) break;
        }

        free(used);

        if (idx == n) {
            *returnSize = n;
            return res;
        }
    }

    free(res);
    return NULL;        
}
