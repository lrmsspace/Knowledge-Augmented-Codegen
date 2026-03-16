// Source: https://leetcode.com/problems/sum-of-total-strength-of-wizards/   |   Difficulty: Hard
//
// Problem Description:
// As the ruler of a kingdom, you have an army of wizards at your command.
//
// You are given a 0-indexed integer array strength, where strength[i] denotes the strength of the ith wizard. For a contiguous group of wizards (i.e. the wizards' strengths form a subarray of strength), the total strength is defined as the product of the following two values:
//
//
// 	The strength of the weakest wizard in the group.
// 	The total of all the individual strengths of the wizards in the group.
//
//
// Return the sum of the total strengths of all contiguous groups of wizards. Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: strength = [1,3,1,2]
// Output: 44
// Explanation: The following are all the contiguous groups of wizards:
// - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
// - [3] from [1,3,1,2] has a total strength of min([3]) * sum([3]) = 3 * 3 = 9
// - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
// - [2] from [1,3,1,2] has a total strength of min([2]) * sum([2]) = 2 * 2 = 4
// - [1,3] from [1,3,1,2] has a total strength of min([1,3]) * sum([1,3]) = 1 * 4 = 4
// - [3,1] from [1,3,1,2] has a total strength of min([3,1]) * sum([3,1]) = 1 * 4 = 4
// - [1,2] from [1,3,1,2] has a total strength of min([1,2]) * sum([1,2]) = 1 * 3 = 3
// - [1,3,1] from [1,3,1,2] has a total strength of min([1,3,1]) * sum([1,3,1]) = 1 * 5 = 5
// - [3,1,2] from [1,3,1,2] has a total strength of min([3,1,2]) * sum([3,1,2]) = 1 * 6 = 6
// - [1,3,1,2] from [1,3,1,2] has a total strength of min([1,3,1,2]) * sum([1,3,1,2]) = 1 * 7 = 7
// The sum of all the total strengths is 1 + 9 + 1 + 4 + 4 + 4 + 3 + 5 + 6 + 7 = 44.
//
// Constraints:
// 1 <= strength.length <= 105
// 	1 <= strength[i] <= 109
//

int totalStrength(int* strength, int strengthSize) {
    const int MOD = 1000000007;
    long long result = 0;

    // Next smaller element to the left
    int *left = (int*)malloc(strengthSize * sizeof(int));
    // Next smaller element to the right
    int *right = (int*)malloc(strengthSize * sizeof(int));
    // Prefix sums
    long long *prefixSum = (long long*)malloc((strengthSize + 1) * sizeof(long long));
    // Prefix of prefix sums
    long long *prefixPrefixSum = (long long*)malloc((strengthSize + 2) * sizeof(long long));

    // Calculate next smaller elements
    int *stack = (int*)malloc(strengthSize * sizeof(int));
    int top = -1;

    for (int i = 0; i < strengthSize; ++i) {
        while (top >= 0 && strength[stack[top]] >= strength[i]) {
            right[stack[top]] = i;
            --top;
        }
        stack[++top] = i;
    }
    while (top >= 0) {
        right[stack[top]] = strengthSize;
        --top;
    }

    for (int i = strengthSize - 1; i >= 0; --i) {
        while (top >= 0 && strength[stack[top]] > strength[i]) {
            left[stack[top]] = i;
            --top;
        }
        stack[++top] = i;
    }
    while (top >= 0) {
        left[stack[top]] = -1;
        --top;
    }
    free(stack);

    // Calculate prefix sums and prefix of prefix sums
    prefixSum[0] = 0;
    for (int i = 0; i < strengthSize; ++i) {
        prefixSum[i + 1] = (prefixSum[i] + strength[i]) % MOD;
    }
    prefixPrefixSum[0] = 0;
    for (int i = 0; i <= strengthSize; ++i) {
        prefixPrefixSum[i + 1] = (prefixPrefixSum[i] + prefixSum[i]) % MOD;
    }

    // Calculate result
    for (int i = 0; i < strengthSize; ++i) {
        int l = left[i];
        int r = right[i];

        long long totalLeft = (prefixPrefixSum[i + 1] - prefixPrefixSum[l + 1] + MOD) % MOD;
        long long totalRight = (prefixPrefixSum[r + 1] - prefixPrefixSum[i + 1] + MOD) % MOD;

        long long countLeft = i - l;
        long long countRight = r - i;

        long long total = (totalRight * countLeft % MOD - totalLeft * countRight % MOD + MOD) % MOD;
        result = (result + strength[i] * total) % MOD;
    }
    free(left);
    free(right);
    free(prefixSum);
    free(prefixPrefixSum);
    return (int)result;
}
