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
// - Finding Bridges Online (graph, tree, union-find, counting)
//   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
//   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
//   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
//   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
//   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int rootCount(int** edges, int edgesSize, int* edgesColSize, int** guesses, int guessesSize, int* guessesColSize, int k) {
     // Step 1: Build the tree from the edges array
    int n = edgesSize + 1; // Number of nodes is edges + 1
    int* children[n];
    int childrenCount[n];
    for (int i = 0; i < n; i++) {
        childrenCount[i] = 0;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        children[u][childrenCount[u]++] = v;
        children[v][childrenCount[v]++] = u;
    }

    // Step 2: Create a set to store guesses for O(1) lookups
    bool guessSet[n][n]; // guessSet[u][v] is true if u is guessed as parent of v
    memset(guessSet, false, sizeof(guessSet));
    for (int i = 0; i < guessesSize; i++) {
        int parent = guesses[i][0];
        int child = guesses[i][1];
        guessSet[parent][child] = true;
    }

    // Step 3: Perform a DFS to calculate correct guesses for the initial root (let's choose node 0)
    int correctGuessesForRoot0 = 0;

    void dfs(int node, int parent) {
        for (int i = 0; i < childrenCount[node]; i++) {
            int child = children[node][i];
            if (child == parent) continue; // Skip the parent node
            if (guessSet[node][child]) {
                correctGuessesForRoot0++;
            }
            dfs(child, node);
        }
    }
    
    dfs(0, -1);

    // Step 4: Use a second DFS to calculate correct guesses for all other potential roots
    int resultCount = 0;

    void reroot(int node, int parent, int currentCorrectGuesses) {
        if (currentCorrectGuesses >= k) {
            resultCount++;
        }
        
        for (int i = 0; i < childrenCount[node]; i++) {
            int child = children[node][i];
            if (child == parent) continue; // Skip the parent node
            
            // Calculate new correct guesses if we reroot at child
            int newCorrectGuesses = currentCorrectGuesses;
            if (guessSet[node][child]) {
                newCorrectGuesses--; // This guess is no longer correct when child becomes root
            }
            if (guessSet[child][node]) {
                newCorrectGuesses++; // This guess becomes correct when child becomes root
            }
            reroot(child, node, newCorrectGuesses);
        }
    }
    reroot(0, -1, correctGuessesForRoot0);
    return resultCount;
}
