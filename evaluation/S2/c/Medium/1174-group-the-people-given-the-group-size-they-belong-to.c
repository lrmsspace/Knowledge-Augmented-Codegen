// Source: https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/   |   Difficulty: Medium
//
// Problem Description:
// There are n people that are split into some unknown number of groups. Each person is labeled with a unique ID from 0 to n - 1.
//
// You are given an integer array groupSizes, where groupSizes[i] is the size of the group that person i is in. For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.
//
// Return a list of groups such that each person i is in a group of size groupSizes[i].
//
// Each person should appear in exactly one group, and every person must be in a group. If there are multiple answers, return any of them. It is guaranteed that there will be at least one valid solution for the given input.
//
// Example:
// Input: groupSizes = [3,3,3,3,3,1,3]
// Output: [[5],[0,1,2],[3,4,6]]
// Explanation: 
// The first group is [5]. The size is 1, and groupSizes[5] = 1.
// The second group is [0,1,2]. The size is 3, and groupSizes[0] = groupSizes[1] = groupSizes[2] = 3.
// The third group is [3,4,6]. The size is 3, and groupSizes[3] = groupSizes[4] = groupSizes[6] = 3.
// Other possible solutions are [[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].
//
// Constraints:
// groupSizes.length == n
// 	1 <= n <= 500
// 	1 <= groupSizes[i] <= n
//
// Helpful references (internal KB):
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
// - Search for connected components in a graph (stack, graph, dfs, recursion)
//   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
//   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
//   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
//   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
//   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
//   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
//   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
//   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
//   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes) {
    int** buckets = (int**)malloc((groupSizesSize + 1) * sizeof(int*));
    int* bucketSizes = (int*)calloc(groupSizesSize + 1, sizeof(int));
    int* bucketCounts = (int*)calloc(groupSizesSize + 1, sizeof(int));

    for (int i = 0; i <= groupSizesSize; ++i) {
        buckets[i] = (int*)malloc(groupSizesSize * sizeof(int));
    }

    for (int i = 0; i < groupSizesSize; ++i) {
        int size = groupSizes[i];
        buckets[size][bucketCounts[size]++] = i;
        if (bucketCounts[size] == size) {
            bucketSizes[size]++;
            bucketCounts[size] = 0;
        }
    }

    int totalGroups = 0;
    for (int i = 1; i <= groupSizesSize; ++i) {
        totalGroups += bucketSizes[i];
    }

    int** result = (int**)malloc(totalGroups * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalGroups * sizeof(int));
    int index = 0;

    for (int size = 1; size <= groupSizesSize; ++size) {
        for (int j = 0; j < bucketSizes[size]; ++j) {
            result[index] = (int*)malloc(size * sizeof(int));
            memcpy(result[index], buckets[size] + j * size, size * sizeof(int));
            (*returnColumnSizes)[index++] = size;
        }
    }

    for (int i = 0; i <= groupSizesSize; ++i) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
    free(bucketCounts);

    *returnSize = totalGroups;
    return result;      
}
