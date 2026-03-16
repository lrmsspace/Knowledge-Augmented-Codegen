// Source: https://leetcode.com/problems/minimum-cost-to-cut-a-stick/   |   Difficulty: Hard
//
// Problem Description:
// Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is labelled as follows:
//
// Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
//
// You should perform the cuts in order, you can change the order of the cuts as you wish.
//
// The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). Please refer to the first example for a better explanation.
//
// Return the minimum total cost of the cuts.
//
// Example:
// Input: n = 7, cuts = [1,3,4,5]
// Output: 16
// Explanation: Using cuts order = [1, 3, 4, 5] as in the input leads to the following scenario:
//
// The first cut is done to a rod of length 7 so the cost is 7. The second cut is done to a rod of length 6 (i.e. the second part of the first cut), the third is done to a rod of length 4 and the last cut is to a rod of length 3. The total cost is 7 + 6 + 4 + 3 = 20.
// Rearranging the cuts to be [3, 5, 1, 4] for example will lead to a scenario with total cost = 16 (as shown in the example photo 7 + 4 + 3 + 2 = 16).
//
// Constraints:
// 2 <= n <= 106
// 	1 <= cuts.length <= min(n - 1, 100)
// 	1 <= cuts[i] <= n - 1
// 	All the integers in cuts array are distinct.
//
// Helpful references (internal KB):
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minCost(int n, int* cuts, int cutsSize) {
    int size = cutsSize + 2;
    int *arr = (int*)malloc(size * sizeof(int));
    if (!arr) return 0; /* allocation failure */
    arr[0] = 0;
    memcpy(arr + 1, cuts, cutsSize * sizeof(int));
    arr[size - 1] = n;
    /* sort the cuts including the two ends */
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    /* dp[l][r]: min cost to cut stick from arr[l] to arr[r] */
    int **dp = (int**)malloc(size * sizeof(int*));
    if (!dp) { free(arr); return 0; } /* allocation failure */
    for (int i = 0; i < size; ++i) {
        dp[i] = (int*)calloc(size, sizeof(int));
        if (!dp[i]) {
            for (int k = 0; k < i; ++k) free(dp[k]);
            free(dp); free(arr); return 0; /* allocation failure */
        }
    }

    for (int len = 2; len < size; ++len) { /* length of interval */
        for (int l = 0; l + len < size; ++l) {
            int r = l + len;
            dp[l][r] = 1e9;
            for (int k = l + 1; k < r; ++k) { /* possible cut positions */
                int cost = dp[l][k] + dp[k][r] + (arr[r] - arr[l]);
                if (cost < dp[l][r]) dp[l][r] = cost;
            }
        }
    }

    int result = dp[0][size - 1];

    for (int i = 0; i < size; ++i) free(dp[i]);
    free(dp);
    free(arr);
    return result;      
}
