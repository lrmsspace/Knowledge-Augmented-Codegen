// Source: https://leetcode.com/problems/concatenated-divisibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and a positive integer k.
//
// A permutation of nums is said to form a divisible concatenation if, when you concatenate the decimal representations of the numbers in the order specified by the permutation, the resulting number is divisible by k.
//
// Return the lexicographically smallest permutation (when considered as a list of integers) that forms a divisible concatenation. If no such permutation exists, return an empty list.
//
// Example:
// Input: nums = [3,12,45], k = 5
//
// Output: [3,12,45]
//
// Explanation:
//
//
// 	
// 		
// 			Permutation
// 			Concatenated Value
// 			Divisible by 5
// 		
// 	
// 	
// 		
// 			[3, 12, 45]
// 			31245
// 			Yes
// 		
// 		
// 			[3, 45, 12]
// 			34512
// 			No
// 		
// 		
// 			[12, 3, 45]
// 			12345
// 			Yes
// 		
// 		
// 			[12, 45, 3]
// 			12453
// 			No
// 		
// 		
// 			[45, 3, 12]
// 			45312
// 			No
// 		
// 		
// 			[45, 12, 3]
// 			45123
// 			No
// 		
// 	
//
//
// The lexicographically smallest permutation that forms a divisible concatenation is [3,12,45].
//
// Constraints:
// 1 <= nums.length <= 13
// 	1 <= nums[i] <= 105
// 	1 <= k <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* concatenatedDivisibility(int* nums, int numsSize, int k, int* returnSize) {
    if (!returnSize) return NULL;

    int totalPerms = 1;
    for (int i = 2; i <= numsSize; ++i) totalPerms *= i;

    int *indices = (int*)malloc(numsSize * sizeof(int));
    if (!indices) return NULL;
    for (int i = 0; i < numsSize; ++i) indices[i] = i;

    int *bestPerm = NULL;

    for (int perm = 0; perm < totalPerms; ++perm) {
        // Generate the next permutation using Heap's algorithm
        if (perm > 0) {
            int j = numsSize - 1;
            while (j > 0 && indices[j - 1] >= indices[j]) j--;
            if (j == 0) break;
            int l = numsSize - 1;
            while (indices[j - 1] >= indices[l]) l--;
            int temp = indices[j - 1];
            indices[j - 1] = indices[l];
            indices[l] = temp;
            for (int m = j, n = numsSize - 1; m < n; m++, n--) {
                temp = indices[m];
                indices[m] = indices[n];
                indices[n] = temp;
            }
        }

        // Check divisibility
        long long concatNum = 0;
        for (int i = 0; i < numsSize; ++i) {
            concatNum = concatNum * pow(10, (int)log10(nums[indices[i]]) + 1) + nums[indices[i]];
            concatNum %= k; // Keep it manageable
        }
        if (concatNum % k == 0) {
            // Found a valid permutation
            int *currentPerm = (int*)malloc(numsSize * sizeof(int));
            if (!currentPerm) {
                free(indices);
                free(bestPerm);
                return NULL;
            }
            for (int i = 0; i < numsSize; ++i) {
                currentPerm[i] = nums[indices[i]];
            }
            // Check if it's the best lexicographically
            if (!bestPerm || memcmp(currentPerm, bestPerm, numsSize * sizeof(int)) < 0) {
                free(bestPerm);
                bestPerm = currentPerm;
            } else {
                free(currentPerm);      
            }
        }
    }
    free(indices);
    if (bestPerm) {
        *returnSize = numsSize;
        return bestPerm;
    } else {
        *returnSize = 0;
        return NULL;
    }
}
