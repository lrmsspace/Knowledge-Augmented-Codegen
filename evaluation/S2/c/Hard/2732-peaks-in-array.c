// Source: https://leetcode.com/problems/peaks-in-array/   |   Difficulty: Hard
//
// Problem Description:
// A peak in an array arr is an element that is greater than its previous and next element in arr.
//
// You are given an integer array nums and a 2D integer array queries.
//
// You have to process queries of two types:
//
//
// 	queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
// 	queries[i] = [2, indexi, vali], change nums[indexi] to vali.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Notes:
//
//
// 	The first and the last element of an array or a subarray cannot be a peak.
//
// Example:
// Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
//
// Output: [0]
//
// Explanation:
//
// First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
//
// Second query: The number of peaks in the [3,1,4,4,5] is 0.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i][0] == 1 or queries[i][0] == 2
// 	For all i that:
// 	
// 		queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
// 		queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Convex hull trick and Li Chao tree (array, number, dp-1d)
//   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
//   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
//   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
//   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
//   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
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
int* countOfPeaks(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Implementing a solution using sqrt decomposition to handle range queries and point updates efficiently.
    int blockSize = (int)sqrt(numsSize);
    int blockCount = (numsSize + blockSize - 1) / blockSize;
    
    // Create blocks and count peaks in each block
    int* blocks = (int*)calloc(blockCount, sizeof(int));
    
    // Function to check if an element is a peak
    int isPeak(int index) {
        if (index <= 0 || index >= numsSize - 1) return 0; // First and last elements cannot be peaks
        return nums[index] > nums[index - 1] && nums[index] > nums[index + 1];
    }
    
    // Initialize blocks with peak counts
    for (int i = 1; i < numsSize - 1; i++) {
        if (isPeak(i)) {
            blocks[i / blockSize]++;
        }
    }
    
    int* results = (int*)malloc(queriesSize * sizeof(int));
    int resultIndex = 0;
    
    for (int i = 0; i < queriesSize; i++) {
        int type = queries[i][0];
        if (type == 1) {
            // Range query: count peaks in the subarray nums[li..ri]
            int li = queries[i][1];
            int ri = queries[i][2];
            int count = 0;
            
            // Count peaks in the full blocks within the range
            for (int j = li / blockSize; j <= ri / blockSize; j++) {
                if (j * blockSize >= li && (j + 1) * blockSize - 1 <= ri) {
                    count += blocks[j];
                } else {
                    // Count peaks in the partial block
                    for (int k = j * blockSize; k < (j + 1) * blockSize && k < numsSize; k++) {
                        if (k >= li && k <= ri && isPeak(k)) {
                            count++;
                        }
                    }
                }
            }
            results[resultIndex++] = count;
        } else if (type == 2) {
            // Point update: change nums[indexi] to vali
            int indexi = queries[i][1];
            int vali = queries[i][2];
            
            // Update the value and adjust peak counts      
            nums[indexi] = vali;
            for (int j = indexi - 1; j <= indexi + 1; j++) {
                if (j > 0 && j < numsSize - 1) {
                    int blockIndex = j / blockSize;
                    if (isPeak(j)) {
                        blocks[blockIndex]++;
                    } else {
                        blocks[blockIndex]--;
                    }
                }
            }
        }
    }
    *returnSize = resultIndex;
    return results;
}
