// Source: https://leetcode.com/problems/count-number-of-possible-root-nodes/   |   Difficulty: Hard
//
// Problem Description:
// Alice has an undirected tree with n nodes labeled from 0 to n - 1. The tree is represented as a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Alice wants Bob to find the root of the tree. She allows Bob to make several guesses about her tree. In one guess, he does the following:
//
//
// 	Chooses two distinct integers u and v such that there exists an edge [u, v] in the tree.
// 	He tells Alice that u is the parent of v in the tree.
//
//
// Bob's guesses are represented by a 2D integer array guesses where guesses[j] = [uj, vj] indicates Bob guessed uj to be the parent of vj.
//
// Alice being lazy, does not reply to each of Bob's guesses, but just says that at least k of his guesses are true.
//
// Given the 2D integer arrays edges, guesses and the integer k, return the number of possible nodes that can be the root of Alice's tree. If there is no such tree, return 0.
//
// Example:
// Input: edges = [[0,1],[1,2],[1,3],[4,2]], guesses = [[1,3],[0,1],[1,0],[2,4]], k = 3
// Output: 3
// Explanation: 
// Root = 0, correct guesses = [1,3], [0,1], [2,4]
// Root = 1, correct guesses = [1,3], [1,0], [2,4]
// Root = 2, correct guesses = [1,3], [1,0], [2,4]
// Root = 3, correct guesses = [1,0], [2,4]
// Root = 4, correct guesses = [1,3], [1,0]
// Considering 0, 1, or 2 as root node leads to 3 correct guesses.
//
// Constraints:
// edges.length == n - 1
// 	2 <= n <= 105
// 	1 <= guesses.length <= 105
// 	0 <= ai, bi, uj, vj <= n - 1
// 	ai != bi
// 	uj != vj
// 	edges represents a valid tree.
// 	guesses[j] is an edge of the tree.
// 	guesses is unique.
// 	0 <= k <= guesses.length
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        unordered_set<long long> guessSet;
        for (const auto& guess : guesses) {
            guessSet.insert(((long long)guess[0] << 32) | guess[1]);
        }

        vector<int> parent(n, -1);
        function<void(int, int)> dfs = [&](int node, int par) {
            parent[node] = par;
            for (int neighbor : graph[node]) {
                if (neighbor != par) {
                    dfs(neighbor, node);
                }
            }
        };
        dfs(0, -1);

        int correctGuesses = 0;
        for (const auto& guess : guesses) {
            if (parent[guess[1]] == guess[0]) {
                correctGuesses++;
            }
        }

        int result = 0;
        function<void(int, int, int)> reroot = [&](int node, int par, int currCorrect) {
            if (currCorrect >= k) {
                result++;
            }
            for (int neighbor : graph[node]) {
                if (neighbor != par) {
                    int nextCorrect = currCorrect;
                    if (guessSet.count(((long long)node << 32) | neighbor)) {
                        nextCorrect--;
                    }
                    if (guessSet.count(((long long)neighbor << 32) | node)) {
                        nextCorrect++;
                    }
                    reroot(neighbor, node, nextCorrect);
                }
            }
        };
        reroot(0, -1, correctGuesses);

        return result;          
    }
};
