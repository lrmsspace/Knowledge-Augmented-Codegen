// Source: https://leetcode.com/problems/candy/   |   Difficulty: Hard
//
// Problem Description:
// There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
//
// You are giving candies to these children subjected to the following requirements:
//
//
// 	Each child must have at least one candy.
// 	Children with a higher rating get more candies than their neighbors.
//
//
// Return the minimum number of candies you need to have to distribute the candies to the children.
//
// Example:
// Input: ratings = [1,0,2]
// Output: 5
// Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
//
// Constraints:
// n == ratings.length
// 	1 <= n <= 2 * 104
// 	0 <= ratings[i] <= 2 * 104
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Longest Increasing Subsequence (array, dp-1d)
//   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
//   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
//   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
//   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int candy(int* ratings, int ratingsSize) {
    int i;
    int* leftToRight = NULL;
    int* rightToLeft = NULL;
    int totalCandies;

    if (ratingsSize <= 0) {
        return 0;
    }

    leftToRight = (int*)malloc((size_t)ratingsSize * sizeof(int));
    rightToLeft = (int*)malloc((size_t)ratingsSize * sizeof(int));
    if (leftToRight == NULL || rightToLeft == NULL) {
        free(leftToRight);
        free(rightToLeft);
        return 0;
    }

    leftToRight[0] = 1;
    for (i = 1; i < ratingsSize; i++) {
        leftToRight[i] = (ratings[i] > ratings[i - 1]) ? (leftToRight[i - 1] + 1) : 1;
    }

    rightToLeft[ratingsSize - 1] = 1;
    for (i = ratingsSize - 2; i >= 0; i--) {
        rightToLeft[i] = (ratings[i] > ratings[i + 1]) ? (rightToLeft[i + 1] + 1) : 1;
    }

    totalCandies = 0;
    for (i = 0; i < ratingsSize; i++) {
        totalCandies += (leftToRight[i] > rightToLeft[i]) ? leftToRight[i] : rightToLeft[i];
    }

    free(leftToRight);
    free(rightToLeft);
    return totalCandies;        
}
