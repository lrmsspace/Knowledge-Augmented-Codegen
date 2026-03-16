// Source: https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
//
// You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Remove two distinct edges of the tree to form three connected components. For a pair of removed edges, the following steps are defined:
//
//
// 	Get the XOR of all the values of the nodes for each of the three components respectively.
// 	The difference between the largest XOR value and the smallest XOR value is the score of the pair.
//
//
//
// 	For example, say the three components have the node values: [4,5,7], [1,9], and [3,3,3]. The three XOR values are 4 ^ 5 ^ 7 = 6, 1 ^ 9 = 8, and 3 ^ 3 ^ 3 = 3. The largest XOR value is 8 and the smallest XOR value is 3. The score is then 8 - 3 = 5.
//
//
// Return the minimum score of any possible pair of edge removals on the given tree.
//
// Example:
// Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
// Output: 9
// Explanation: The diagram above shows a way to make a pair of removals.
// - The 1st component has nodes [1,3,4] with values [5,4,11]. Its XOR value is 5 ^ 4 ^ 11 = 10.
// - The 2nd component has node [0] with value [1]. Its XOR value is 1 = 1.
// - The 3rd component has node [2] with value [5]. Its XOR value is 5 = 5.
// The score is the difference between the largest and smallest XOR value which is 10 - 1 = 9.
// It can be shown that no other pair of removals will obtain a smaller score than 9.
//
// Constraints:
// n == nums.length
// 	3 <= n <= 1000
// 	1 <= nums[i] <= 108
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Finding Bridges Online (ds, tree, union-find, lca, rerooting)
//   • When to use: Use this algorithm to dynamically maintain bridges and 2-edge-connected components in a graph as edges are added. It efficiently processes edge additions by updating forest structures and compressing cycles.
//   • Idea: This algorithm dynamically maintains bridges and 2-edge-connected components using two DSU structures and a parent array for tree structure. Edge additions involve re-rooting smaller trees and compressing cycles via LCA, achieving amortized O(log N) per edge operation.
//   • Invariants: The par[] array always defines a forest structure where each tree corresponds to a connected component of 2-edge-connected components.; Each 2-edge-connected component is represented by a single canonical element in its dedicated DSU structure.
//   • Tips: Employ two DSU structures: one for connected components and another for 2-edge-connected components.; Optimize re-rooting operations by always re-rooting the smaller of the two trees being joined.
//   • Pitfalls: Failing to consistently update both DSU structures and the parent array after operations.; Incorrectly handling parent pointers during re-rooting, leading to broken tree structures.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumScore(int* nums, int numsSize, int** edges, int edgesSize, int* edgesColSize) {
    #define MAX_NODES 1000

    typedef struct AdjNode {
        int to;
        struct AdjNode* next;
    } AdjNode;

    AdjNode* graph[MAX_NODES] = {0};
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        AdjNode* nodeU = (AdjNode*)malloc(sizeof(AdjNode));
        nodeU->to = v;
        nodeU->next = graph[u];
        graph[u] = nodeU;

        AdjNode* nodeV = (AdjNode*)malloc(sizeof(AdjNode));
        nodeV->to = u;
        nodeV->next = graph[v];
        graph[v] = nodeV;
    }

    int parent[MAX_NODES];
    int subtreeXOR[MAX_NODES];
    int visited[MAX_NODES] = {0};

    long long totalXOR = 0;
    for (int i = 0; i < numsSize; i++) {
        totalXOR ^= nums[i];
    }

    void dfs(int node, int par) {
        visited[node] = 1;
        subtreeXOR[node] = nums[node];
        parent[node] = par;

        AdjNode* adj = graph[node];
        while (adj) {
            int neighbor = adj->to;
            if (!visited[neighbor]) {
                dfs(neighbor, node);
                subtreeXOR[node] ^= subtreeXOR[neighbor];
            }
            adj = adj->next;
        }
    }

    dfs(0, -1);

    long long minScore = 1e15;

    for (int i = 0; i < edgesSize; i++) {
        int u1 = edges[i][0];
        int v1 = edges[i][1];
        if (parent[v1] == u1) {
            int temp = u1;
            u1 = v1;
            v1 = temp;
        }

        for (int j = i + 1; j < edgesSize; j++) {
            int u2 = edges[j][0];
            int v2 = edges[j][1];
            if (parent[v2] == u2) {
                int temp = u2;
                u2 = v2;
                v2 = temp;
            }

            long long xor1, xor2, xor3;

            if (isAncestor(u1, u2)) {
                xor1 = subtreeXOR[u2];
                xor2 = subtreeXOR[u1] ^ subtreeXOR[u2];
                xor3 = totalXOR ^ subtreeXOR[u1];
            } else if (isAncestor(u2, u1)) {
                xor1 = subtreeXOR[u1];
                xor2 = subtreeXOR[u2] ^ subtreeXOR[u1];
                xor3 = totalXOR ^ subtreeXOR[u2];
            } else {
                xor1 = subtreeXOR[u1];
                xor2 = subtreeXOR[u2];
                xor3 = totalXOR ^ subtreeXOR[u1] ^ subtreeXOR[u2];
            }

            long long maxXOR = xor1 > xor2 ? (xor1 > xor3 ? xor1 : xor3) : (xor2 > xor3 ? xor2 : xor3);
            long long minXOR = xor1 < xor2 ? (xor1 < xor3 ? xor1 : xor3) : (xor2 < xor3 ? xor2 : xor3);
            long long score = maxXOR - minXOR;

            if (score < minScore) {
                minScore = score;
            }
        }
    }
    return (int)minScore;
}
