// Source: https://leetcode.com/problems/fair-distribution-of-cookies/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array cookies, where cookies[i] denotes the number of cookies in the ith bag. You are also given an integer k that denotes the number of children to distribute all the bags of cookies to. All the cookies in the same bag must go to the same child and cannot be split up.
//
// The unfairness of a distribution is defined as the maximum total cookies obtained by a single child in the distribution.
//
// Return the minimum unfairness of all distributions.
//
// Example:
// Input: cookies = [8,15,10,20,8], k = 2
// Output: 31
// Explanation: One optimal distribution is [8,15,8] and [10,20]
// - The 1st child receives [8,15,8] which has a total of 8 + 15 + 8 = 31 cookies.
// - The 2nd child receives [10,20] which has a total of 10 + 20 = 30 cookies.
// The unfairness of the distribution is max(31,30) = 31.
// It can be shown that there is no distribution with an unfairness less than 31.
//
// Constraints:
// 2 <= cookies.length <= 8
// 	1 <= cookies[i] <= 105
// 	2 <= k <= cookies.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int distributeCookies(int* cookies, int cookiesSize, int k) {
    int ans = 1e9;

    void backtrack(int index, int* distribution, int distributionSize) {
        if (index == cookiesSize) {
            int maxCookies = 0;
            for (int i = 0; i < distributionSize; i++) {
                if (distribution[i] > maxCookies) {
                    maxCookies = distribution[i];
                }
            }
            if (maxCookies < ans) {
                ans = maxCookies;
            }
            return;
        }

        for (int i = 0; i < distributionSize; i++) {
            distribution[i] += cookies[index];
            backtrack(index + 1, distribution, distributionSize);
            distribution[i] -= cookies[index];
            if (distribution[i] == 0) {
                break;
            }
        }
    }

    int* distribution = (int*)calloc(k, sizeof(int));
    backtrack(0, distribution, k);
    free(distribution);

    return ans;     
}
