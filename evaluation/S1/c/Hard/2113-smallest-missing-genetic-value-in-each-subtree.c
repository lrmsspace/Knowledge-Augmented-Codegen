// Source: https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/   |   Difficulty: Hard
//
// Problem Description:
// There is a family tree rooted at 0 consisting of n nodes numbered 0 to n - 1. You are given a 0-indexed integer array parents, where parents[i] is the parent for node i. Since node 0 is the root, parents[0] == -1.
//
// There are 105 genetic values, each represented by an integer in the inclusive range [1, 105]. You are given a 0-indexed integer array nums, where nums[i] is a distinct genetic value for node i.
//
// Return an array ans of length n where ans[i] is the smallest genetic value that is missing from the subtree rooted at node i.
//
// The subtree rooted at a node x contains node x and all of its descendant nodes.
//
// Example:
// Input: parents = [-1,0,0,2], nums = [1,2,3,4]
// Output: [5,1,1,1]
// Explanation: The answer for each subtree is calculated as follows:
// - 0: The subtree contains nodes [0,1,2,3] with values [1,2,3,4]. 5 is the smallest missing value.
// - 1: The subtree contains only node 1 with value 2. 1 is the smallest missing value.
// - 2: The subtree contains nodes [2,3] with values [3,4]. 1 is the smallest missing value.
// - 3: The subtree contains only node 3 with value 4. 1 is the smallest missing value.
//
// Constraints:
// n == parents.length == nums.length
// 	2 <= n <= 105
// 	0 <= parents[i] <= n - 1 for i != 0
// 	parents[0] == -1
// 	parents represents a valid tree.
// 	1 <= nums[i] <= 105
// 	Each nums[i] is distinct.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
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
int* smallestMissingValueSubtree(int* parents, int parentsSize, int* nums, int numsSize, int* returnSize) {
    int *result = (int*)malloc(parentsSize * sizeof(int));
    for (int i = 0; i < parentsSize; i++) {
        result[i] = 1;
    }

    // Build adjacency list for the tree
    int **children = (int**)malloc(parentsSize * sizeof(int*));
    int *childCounts = (int*)calloc(parentsSize, sizeof(int));
    for (int i = 0; i < parentsSize; i++) {
        children[i] = (int*)malloc(parentsSize * sizeof(int));
    }
    for (int i = 1; i < parentsSize; i++) {
        int p = parents[i];
        children[p][childCounts[p]++] = i;
    }

    // Find the node with genetic value 1
    int startNode = -1;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            startNode = i;
            break;
        }
    }
    if (startNode == -1) {
        // If no node has genetic value 1, all results are 1
        for (int i = 0; i < parentsSize; i++) {
            result[i] = 1;
        }
        // Free memory
        for (int i = 0; i < parentsSize; i++) {
            free(children[i]);
        }
        free(children);
        free(childCounts);
        *returnSize = parentsSize;
        return result;
    }

    // Track present genetic values
    bool *present = (bool*)calloc(100006, sizeof(bool));
    int missingValue = 1;

    // DFS to mark present genetic values in subtree
    void dfs(int node) {
        present[nums[node]] = true;
        for (int i = 0; i < childCounts[node]; i++) {
            dfs(children[node][i]);
        }
    }

    // Traverse from startNode to root
    int currentNode = startNode;
    while (currentNode != -1) {
        dfs(currentNode);
        while (present[missingValue]) {
            missingValue++;
        }
        result[currentNode] = missingValue;
        currentNode = parents[currentNode];
    }

    // Free memory
    for (int i = 0; i < parentsSize; i++) {
        free(children[i]);
    }
    free(children);
    free(childCounts);
    free(present);
    *returnSize = parentsSize;
    return result;
}
