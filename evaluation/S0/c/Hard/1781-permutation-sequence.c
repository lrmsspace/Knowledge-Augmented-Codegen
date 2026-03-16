// Source: https://leetcode.com/problems/permutation-sequence/   |   Difficulty: Hard
//
// Problem Description:
// The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
//
// By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
//
//
// 	"123"
// 	"132"
// 	"213"
// 	"231"
// 	"312"
// 	"321"
//
//
// Given n and k, return the kth permutation sequence.
//
// Example:
// Input: n = 3, k = 3
// Output: "213"
//
// Constraints:
// 1 <= n <= 9
// 	1 <= k <= n!
//

char* getPermutation(int n, int k) {
    int fact[10];
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
    }

    char *nums = (char*)malloc(n + 1);
    for (int i = 0; i < n; i++) {
        nums[i] = '1' + i;
    }
    nums[n] = '\0';

    k--; // Convert to zero-based index
    char *result = (char*)malloc(n + 1);
    result[n] = '\0';

    for (int i = 0; i < n; i++) {
        int idx = k / fact[n - 1 - i];
        result[i] = nums[idx];

        // Remove used number from nums
        for (int j = idx; j < n - 1 - i; j++) {
            nums[j] = nums[j + 1];
        }

        k %= fact[n - 1 - i];
    }

    free(nums);
    return result;      
}
