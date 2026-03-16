// Source: https://leetcode.com/problems/maximum-segment-sum-after-removals/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums and removeQueries, both of length n. For the ith query, the element in nums at the index removeQueries[i] is removed, splitting nums into different segments.
//
// A segment is a contiguous sequence of positive integers in nums. A segment sum is the sum of every element in a segment.
//
// Return an integer array answer, of length n, where answer[i] is the maximum segment sum after applying the ith removal.
//
// Note: The same index will not be removed more than once.
//
// Example:
// Input: nums = [1,2,5,6,1], removeQueries = [0,3,2,4,1]
// Output: [14,7,2,2,0]
// Explanation: Using 0 to indicate a removed element, the answer is as follows:
// Query 1: Remove the 0th element, nums becomes [0,2,5,6,1] and the maximum segment sum is 14 for segment [2,5,6,1].
// Query 2: Remove the 3rd element, nums becomes [0,2,5,0,1] and the maximum segment sum is 7 for segment [2,5].
// Query 3: Remove the 2nd element, nums becomes [0,2,0,0,1] and the maximum segment sum is 2 for segment [2]. 
// Query 4: Remove the 4th element, nums becomes [0,2,0,0,0] and the maximum segment sum is 2 for segment [2]. 
// Query 5: Remove the 1st element, nums becomes [0,0,0,0,0] and the maximum segment sum is 0, since there are no segments.
// Finally, we return [14,7,2,2,0].
//
// Constraints:
// n == nums.length == removeQueries.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= 109
// 	0 <= removeQueries[i] < n
// 	All the values of removeQueries are unique.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
//   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
//   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
//   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
//   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
//   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* maximumSegmentSum(int* nums, int numsSize, int* removeQueries, int removeQueriesSize, int* returnSize) {
    *returnSize = removeQueriesSize;
    long long* result = (long long*)malloc(removeQueriesSize * sizeof(long long));
    if (!result) return NULL;

    // Union-Find (Disjoint Set Union) structure
    int* parent = (int*)malloc(numsSize * sizeof(int));
    long long* segSum = (long long*)malloc(numsSize * sizeof(long long));
    if (!parent || !segSum) {
        free(result);
        free(parent);
        free(segSum);
        return NULL;
    }
    for (int i = 0; i < numsSize; i++) {
        parent[i] = -1; // -1 indicates removed
        segSum[i] = 0;
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union two segments
    void unionSegments(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
            segSum[rootX] += segSum[rootY];
        }
    }

    long long currentMax = 0;
    for (int i = removeQueriesSize - 1; i >= 0; i--) {
        result[i] = currentMax;
        int idx = removeQueries[i];
        parent[idx] = idx; // Add back the element
        segSum[idx] = nums[idx];

        // Union with left segment if exists
        if (idx > 0 && parent[idx - 1] != -1) {
            unionSegments(idx, idx - 1);
        }
        // Union with right segment if exists
        if (idx < numsSize - 1 && parent[idx + 1] != -1) {
            unionSegments(idx, idx + 1);
        }

        int root = find(idx);
        if (segSum[root] > currentMax) {
            currentMax = segSum[root];
        }
    }

    free(parent);
    free(segSum);
    return result;      
}
