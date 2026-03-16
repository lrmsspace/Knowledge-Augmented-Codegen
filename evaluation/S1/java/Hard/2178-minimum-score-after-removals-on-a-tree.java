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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumScore(int[] nums, int[][] edges) {
        int n = nums.length;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        int[] subXor = new int[n];
        int[] inTime = new int[n];
        int[] outTime = new int[n];
        int[] euler = new int[2 * n - 1];
        int time = 0;

        // DFS to compute subtree XORs and Euler tour
        Deque<int[]> stack = new ArrayDeque<>();
        stack.push(new int[]{0, -1, 0}); // node, parent, state
        while (!stack.isEmpty()) {
            int[] curr = stack.pop();
            int node = curr[0], parent = curr[1], state = curr[2];

            if (state == 0) { // Pre-order
                inTime[node] = time;
                euler[time++] = node;
                subXor[node] = nums[node];
                stack.push(new int[]{node, parent, 1}); // Post-order

                for (int neighbor : graph.get(node)) {
                    if (neighbor != parent) {
                        stack.push(new int[]{neighbor, node, 0});
                    }
                }
            } else { // Post-order
                outTime[node] = time;
                for (int neighbor : graph.get(node)) {
                    if (neighbor != parent) {
                        subXor[node] ^= subXor[neighbor];
                    }
                }
            }
        }

        int totalXor = subXor[0];
        int minScore = Integer.MAX_VALUE;

        // Check all pairs of edges
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                int a = edges[i][1];
                int b = edges[j][1];

                int xor1, xor2, xor3;

                if (inTime[a] < inTime[b] && outTime[a] > outTime[b]) {
                    // b is in the subtree of a
                    xor1 = subXor[b];
                    xor2 = subXor[a] ^ subXor[b];
                    xor3 = totalXor ^ subXor[a];
                } else if (inTime[b] < inTime[a] && outTime[b] > outTime[a]) {
                    // a is in the subtree of b
                    xor1 = subXor[a];
                    xor2 = subXor[b] ^ subXor[a];
                    xor3 = totalXor ^ subXor[b];
                } else {
                    // a and b are in different subtrees
                    xor1 = subXor[a];
                    xor2 = subXor[b];
                    xor3 = totalXor ^ subXor[a] ^ subXor[b];
                }

                int currentMax = Math.max(xor1, Math.max(xor2, xor3));
                int currentMin = Math.min(xor1, Math.min(xor2, xor3));
                minScore = Math.min(minScore, currentMax - currentMin);
            }
        }
        return minScore;  
    }
}
