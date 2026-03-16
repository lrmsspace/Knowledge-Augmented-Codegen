// Source: https://leetcode.com/problems/find-x-value-of-array-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers nums, and a positive integer k.
//
// You are allowed to perform an operation once on nums, where in each operation you can remove any non-overlapping prefix and suffix from nums such that nums remains non-empty.
//
// You need to find the x-value of nums, which is the number of ways to perform this operation so that the product of the remaining elements leaves a remainder of x when divided by k.
//
// Return an array result of size k where result[x] is the x-value of nums for 0 <= x <= k - 1.
//
// A prefix of an array is a subarray that starts from the beginning of the array and extends to any point within it.
//
// A suffix of an array is a subarray that starts at any point within the array and extends to the end of the array.
//
// Note that the prefix and suffix to be chosen for the operation can be empty.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 3
//
// Output: [9,2,4]
//
// Explanation:
//
//
// 	For x = 0, the possible operations include all possible ways to remove non-overlapping prefix/suffix that do not remove nums[2] == 3.
// 	For x = 1, the possible operations are:
// 	
// 		Remove the empty prefix and the suffix [2, 3, 4, 5]. nums becomes [1].
// 		Remove the prefix [1, 2, 3] and the suffix [5]. nums becomes [4].
// 	
// 	
// 	For x = 2, the possible operations are:
// 	
// 		Remove the empty prefix and the suffix [3, 4, 5]. nums becomes [1, 2].
// 		Remove the prefix [1] and the suffix [3, 4, 5]. nums becomes [2].
// 		Remove the prefix [1, 2, 3] and the empty suffix. nums becomes [4, 5].
// 		Remove the prefix [1, 2, 3, 4] and the empty suffix. nums becomes [5].
//
// Constraints:
// 1 <= nums[i] <= 109
// 	1 <= nums.length <= 105
// 	1 <= k <= 5
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* resultArray(int* nums, int numsSize, int k, int* returnSize) {
    long long* result = (long long*)calloc(k, sizeof(long long));
    int* prefixProdMod = (int*)malloc((numsSize + 1) * sizeof(int));
    int* suffixProdMod = (int*)malloc((numsSize + 1) * sizeof(int));

    prefixProdMod[0] = 1 % k;
    for (int i = 0; i < numsSize; i++) {
        prefixProdMod[i + 1] = (prefixProdMod[i] * (nums[i] % k)) % k;
    }

    suffixProdMod[numsSize] = 1 % k;
    for (int i = numsSize - 1; i >= 0; i--) {
        suffixProdMod[i] = (suffixProdMod[i + 1] * (nums[i] % k)) % k;
    }

    for (int i = 0; i <= numsSize; i++) {
        for (int j = i; j <= numsSize; j++) {
            int prodMod = (prefixProdMod[i] * suffixProdMod[j]) % k;
            result[prodMod]++;
        }
    }

    free(prefixProdMod);
    free(suffixProdMod);

    *returnSize = k;
    return result;      
}
