// Source: https://leetcode.com/problems/maximum-good-subtree-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. Each node i has an integer value vals[i], and its parent is given by par[i].
//
// A subset of nodes within the subtree of a node is called good if every digit from 0 to 9 appears at most once in the decimal representation of the values of the selected nodes.
//
// The score of a good subset is the sum of the values of its nodes.
//
// Define an array maxScore of length n, where maxScore[u] represents the maximum possible sum of values of a good subset of nodes that belong to the subtree rooted at node u, including u itself and all its descendants.
//
// Return the sum of all values in maxScore.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: vals = [2,3], par = [-1,0]
//
// Output: 8
//
// Explanation:
//
//
//
//
// 	The subtree rooted at node 0 includes nodes {0, 1}. The subset {2, 3} is good as the digits 2 and 3 appear only once. The score of this subset is 2 + 3 = 5.
// 	The subtree rooted at node 1 includes only node {1}. The subset {3} is good. The score of this subset is 3.
// 	The maxScore array is [5, 3], and the sum of all values in maxScore is 5 + 3 = 8. Thus, the answer is 8.
//
// Constraints:
// 1 <= n == vals.length <= 500
// 	1 <= vals[i] <= 109
// 	par.length == n
// 	par[0] == -1
// 	0 <= par[i] < n for i in [1, n - 1]
// 	The input is generated such that the parent array par represents a valid tree.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
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

int goodSubtreeSum(int* vals, int valsSize, int* par, int parSize) {
    // This problem can be solved using a depth-first search (DFS) to compute the maximum good subset score for each node in the tree. We will use a bitmask to keep track of which digits have been used in the current subset. The bitmask will have 10 bits, each representing whether a digit from 0 to 9 has been used.

    // Step 1: Build the adjacency list for the tree
    int n = valsSize;
    int* children[n];
    int childrenCount[n];
    for (int i = 0; i < n; i++) {
        childrenCount[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int parent = par[i];
        children[parent][childrenCount[parent]++] = i;
    }

    // Step 2: Define a recursive function to compute the maximum good subset score
    int maxScore[n];
    
    // Helper function to perform DFS and compute maxScore
    void dfs(int node) {
        // Initialize the max score for this node
        maxScore[node] = vals[node];

        // Create a bitmask for the current node's value
        int val = vals[node];
        int digitMask = 0;
        while (val > 0) {
            int digit = val % 10;
            if (digitMask & (1 << digit)) {
                // If this digit is already used, we cannot include this node
                return;
            }
            digitMask |= (1 << digit);
            val /= 10;
        }

        // Explore children
        for (int i = 0; i < childrenCount[node]; i++) {
            int child = children[node][i];
            dfs(child);
            // Check if we can include the child's max score without repeating digits
            if ((digitMask & maxScore[child]) == 0) {
                maxScore[node] += maxScore[child];
                digitMask |= maxScore[child]; // Update the mask with child's digits
            }
        }
    }

    // Step 3: Start DFS from the root node (node 0)
    dfs(0);

    // Step 4: Sum up all values in maxScore and return modulo 10^9 + 7
    long long result = 0;
    for (int i = 0; i < n; i++) {
        result = (result + maxScore[i]) % 1000000007;
    }
    return (int)result;   
}
