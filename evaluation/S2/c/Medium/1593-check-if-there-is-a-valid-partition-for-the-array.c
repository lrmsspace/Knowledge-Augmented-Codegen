// Source: https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. You have to partition the array into one or more contiguous subarrays.
//
// We call a partition of the array valid if each of the obtained subarrays satisfies one of the following conditions:
//
//
// 	The subarray consists of exactly 2, equal elements. For example, the subarray [2,2] is good.
// 	The subarray consists of exactly 3, equal elements. For example, the subarray [4,4,4] is good.
// 	The subarray consists of exactly 3 consecutive increasing elements, that is, the difference between adjacent elements is 1. For example, the subarray [3,4,5] is good, but the subarray [1,3,5] is not.
//
//
// Return true if the array has at least one valid partition. Otherwise, return false.
//
// Example:
// Input: nums = [4,4,4,5,6]
// Output: true
// Explanation: The array can be partitioned into the subarrays [4,4] and [4,5,6].
// This partition is valid, so we return true.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Ternary Search (interval, number, binary-search, enumeration)
//   • When to use: Use Ternary Search to find the minimum or maximum of a unimodal or bitonic function over a continuous or discrete interval. It is effective when the function's derivative is hard to compute or unavailable.
//   • Idea: Ternary search is a divide and conquer algorithm that repeatedly narrows down the search space for the extremum of a unimodal function by evaluating two points within the current interval. It reduces the search interval by one-third in each step, achieving O(log N) time complexity.
//   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with m2 to narrow the search.
//   • Tips: Ensure the function is strictly unimodal or bitonic within the search range.; Handle floating-point precision carefully for continuous functions.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point errors can lead to incorrect bounds or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool validPartition(int* nums, int numsSize) {
    if (numsSize < 2) {
        return false; // A valid partition requires at least 2 elements
    }

    // Create a boolean array to store the validity of partitions up to each index
    bool* dp = (bool*)malloc(numsSize * sizeof(bool));
    if (!dp) {
        return false; // Memory allocation failed
    }
    
    dp[0] = false; // Single element cannot form a valid partition
    dp[1] = (nums[0] == nums[1]); // Two equal elements form a valid partition

    for (int i = 2; i < numsSize; i++) {
        dp[i] = false;
        
        // Check for two equal elements
        if (nums[i] == nums[i - 1]) {
            dp[i] = dp[i] || dp[i - 2]; // Valid if the previous partition is valid
        }
        
        // Check for three equal elements
        if (i >= 2 && nums[i] == nums[i - 1] && nums[i - 1] == nums[i - 2]) {
            dp[i] = dp[i] || dp[i - 3]; // Valid if the partition before the last three is valid
        }
        
        // Check for three consecutive increasing elements
        if (i >= 2 && nums[i] == nums[i - 1] + 1 && nums[i - 1] == nums[i - 2] + 1) {
            dp[i] = dp[i] || dp[i - 3]; // Valid if the partition before the last three is valid
        }
    }

    bool result = dp[numsSize - 1]; // The validity of the entire array partition
    free(dp); // Free allocated memory
    return result;      
}
