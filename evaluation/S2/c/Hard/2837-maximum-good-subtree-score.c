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
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Finding Bridges Online (ds, tree, union-find, lca, rerooting)
//   • When to use: Use this algorithm to dynamically maintain bridges and 2-edge-connected components in a graph as edges are added. It efficiently processes edge additions by updating forest structures and compressing cycles.
//   • Idea: This algorithm dynamically maintains bridges and 2-edge-connected components using two DSU structures and a parent array for tree structure. Edge additions involve re-rooting smaller trees and compressing cycles via LCA, achieving amortized O(log N) per edge operation.
//   • Invariants: The par[] array always defines a forest structure where each tree corresponds to a connected component of 2-edge-connected components.; Each 2-edge-connected component is represented by a single canonical element in its dedicated DSU structure.
//   • Tips: Employ two DSU structures: one for connected components and another for 2-edge-connected components.; Optimize re-rooting operations by always re-rooting the smaller of the two trees being joined.
//   • Pitfalls: Failing to consistently update both DSU structures and the parent array after operations.; Incorrectly handling parent pointers during re-rooting, leading to broken tree structures.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int goodSubtreeSum(int* vals, int valsSize, int* par, int parSize) {
    // Step 1: Build the tree from the parent array
    int n = valsSize;
    int* children[n];
    int childrenCount[n];
    for (int i = 0; i < n; i++) {
        childrenCount[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int p = par[i];
        children[p][childrenCount[p]++] = i;
    }

    // Step 2: Define a recursive function to calculate the maximum good subset score
    int maxScore[n];
    for (int i = 0; i < n; i++) {
        maxScore[i] = 0;
    }

    int mod = 1000000007;

    int dfs(int u) {
        // Create a bitmask to track used digits
        int digitMask = 0;
        int currentScore = vals[u];

        // Check if the current node's value can be included
        int tempVal = vals[u];
        while (tempVal > 0) {
            int digit = tempVal % 10;
            if ((digitMask & (1 << digit)) != 0) {
                return 0; // Digit already used, cannot include this node
            }
            digitMask |= (1 << digit);
            tempVal /= 10;
        }

        // Include the current node's value in the score
        currentScore %= mod;

        // Explore children nodes
        for (int i = 0; i < childrenCount[u]; i++) {
            int child = children[u][i];
            currentScore += dfs(child);
            currentScore %= mod;
        }

        maxScore[u] = currentScore;
        return maxScore[u];
    }

    // Step 3: Start DFS from the root node (0)
    dfs(0);

    // Step 4: Calculate the sum of all values in maxScore
    long long totalMaxScore = 0;
    for (int i = 0; i < n; i++) {
        totalMaxScore += maxScore[i];
        totalMaxScore %= mod;
    }

    return (int)totalMaxScore;
}
