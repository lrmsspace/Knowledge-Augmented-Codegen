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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int rootCount(int** edges, int edgesSize, int* edgesColSize, int** guesses, int guessesSize, int* guessesColSize, int k) {
   
    int n = edgesSize + 1;

    // Build adjacency list for the tree
    typedef struct Node {
        int val;
        struct Node* next;
    } Node;

    Node** graph = (Node**)calloc(n, sizeof(Node*));
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        Node* nodeU = (Node*)malloc(sizeof(Node));
        nodeU->val = v;
        nodeU->next = graph[u];
        graph[u] = nodeU;

        Node* nodeV = (Node*)malloc(sizeof(Node));
        nodeV->val = u;
        nodeV->next = graph[v];
        graph[v] = nodeV;
    }

    // Store guesses in a hash set for O(1) lookup
    #define HASH_SIZE 131071
    typedef struct HashNode {
        int key;
        struct HashNode* next;
    } HashNode;

    HashNode** hashTable = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));

    void insertGuess(int u, int v) {
        int hashIndex = ((u * 31) ^ v) % HASH_SIZE;
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->key = (u << 16) | v;
        newNode->next = hashTable[hashIndex];
        hashTable[hashIndex] = newNode;
    }

    int containsGuess(int u, int v) {
        int hashIndex = ((u * 31) ^ v) % HASH_SIZE;
        HashNode* curr = hashTable[hashIndex];
        int key = (u << 16) | v;
        while (curr) {
            if (curr->key == key) return 1;
            curr = curr->next;
        }
        return 0;
    }

    for (int i = 0; i < guessesSize; i++) {
        insertGuess(guesses[i][0], guesses[i][1]);
    }

    // DFS to count correct guesses for root at node 0
    int* correctGuessesCount = (int*)calloc(n, sizeof(int));
    int totalCorrectGuesses = 0;

    void dfsCount(int node, int parent) {
        Node* neighbor = graph[node];
        while (neighbor) {
            int nextNode = neighbor->val;
            if (nextNode != parent) {
                if (containsGuess(node, nextNode)) {
                    totalCorrectGuesses++;
                }
                dfsCount(nextNode, node);
            }
            neighbor = neighbor->next;
        }
    }
    dfsCount(0, -1);
    correctGuessesCount[0] = totalCorrectGuesses;
    // DFS to re-root the tree and update correct guesses count
    void dfsReroot(int node, int parent) {
        Node* neighbor = graph[node];
        while (neighbor) {
            int nextNode = neighbor->val;
            if (nextNode != parent) {
                correctGuessesCount[nextNode] = correctGuessesCount[node];
                if (containsGuess(node, nextNode)) {
                    correctGuessesCount[nextNode]--;
                }
                if (containsGuess(nextNode, node)) {
                    correctGuessesCount[nextNode]++;
                }
                dfsReroot(nextNode, node);
            }
            neighbor = neighbor->next;
        }
    }
    dfsReroot(0, -1);
    // Count valid roots
    int validRoots = 0; 
    for (int i = 0; i < n; i++) {
        if (correctGuessesCount[i] >= k) {
            validRoots++;
        }
    }
    // Free allocated memory
    for (int i = 0; i < n; i++) {   
        Node* curr = graph[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph);
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = hashTable[i];
        while (curr) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(hashTable);
    free(correctGuessesCount);
    return validRoots;
}
