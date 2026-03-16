// Source: https://leetcode.com/problems/find-array-given-subset-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n representing the length of an unknown array that you are trying to recover. You are also given an array sums containing the values of all 2n subset sums of the unknown array (in no particular order).
//
// Return the array ans of length n representing the unknown array. If multiple answers exist, return any of them.
//
// An array sub is a subset of an array arr if sub can be obtained from arr by deleting some (possibly zero or all) elements of arr. The sum of the elements in sub is one possible subset sum of arr. The sum of an empty array is considered to be 0.
//
// Note: Test cases are generated such that there will always be at least one correct answer.
//
// Example:
// Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
// Output: [1,2,-3]
// Explanation: [1,2,-3] is able to achieve the given subset sums:
// - []: sum is 0
// - [1]: sum is 1
// - [2]: sum is 2
// - [1,2]: sum is 3
// - [-3]: sum is -3
// - [1,-3]: sum is -2
// - [2,-3]: sum is -1
// - [1,2,-3]: sum is 0
// Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will also be accepted.
//
// Constraints:
// 1 <= n <= 15
// 	sums.length == 2n
// 	-104 <= sums[i] <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* recoverArray(int n, int* sums, int sumsSize, int* returnSize) {
    if (!returnSize || sumsSize != (1 << n)) return NULL;
    *returnSize = n;
    int *res = (int*)malloc(n * sizeof(int));
    if (!res) return NULL;

    int size = sumsSize;
    int *currSums = (int*)malloc(size * sizeof(int));
    if (!currSums) { free(res); return NULL; }
    memcpy(currSums, sums, size * sizeof(int));

    for (int i = 0; i < n; ++i) {
        qsort(currSums, size, sizeof(int), (int (*)(const void*, const void*))strcmp);
        int diff = currSums[1] - currSums[0];

        int found = 0;
        for (int sign = -1; sign <= 1; sign += 2) {
            int candidate = sign * diff;
            int halfSize = size / 2;
            int *nextSums = (int*)malloc(halfSize * sizeof(int));
            if (!nextSums) { free(currSums); free(res); return NULL; }

            int *used = (int*)calloc(size, sizeof(int));
            if (!used) { free(nextSums); free(currSums); free(res); return NULL; }

            int idx = 0;
            for (int j = 0; j < size; ++j) {
                if (used[j]) continue;
                nextSums[idx++] = currSums[j];
                int target = currSums[j] + candidate;
                for (int k = j + 1; k < size; ++k) {
                    if (!used[k] && currSums[k] == target) {
                        used[k] = 1;
                        break;
                    }
                }
            }

            free(used);

            if (idx == halfSize) {
                res[i] = candidate;
                free(currSums);
                currSums = nextSums;
                size = halfSize;
                found = 1;
                break;
            } else {
                free(nextSums);
            }
        }

        if (!found) {
            free(currSums);
            free(res);
            return NULL;
        }
    }

    free(currSums);
    return res;     
}
