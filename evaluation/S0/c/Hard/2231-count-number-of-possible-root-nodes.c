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

int rootCount(int** edges, int edgesSize, int* edgesColSize, int** guesses, int guessesSize, int* guessesColSize, int k) {
    int n = edgesSize + 1;
    /* build adjacency list */
    int *adjSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; ++i) {
        adjSizes[edges[i][0]]++;
        adjSizes[edges[i][1]]++;
    }
    int **adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(adjSizes[i] * sizeof(int));
        adjSizes[i] = 0; /* reuse for current size */
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    /* build guess set */
    char *guessSet = (char*)calloc((size_t)n * n, sizeof(char));
    for (int i = 0; i < guessesSize; ++i) {
        int u = guesses[i][0], v = guesses[i][1];
        guessSet[(size_t)u * n + v] = 1;
    }

    /* DFS to count correct guesses with root 0 */
    int *parent = (int*)malloc(n * sizeof(int));
    memset(parent, -1, n * sizeof(int));
    int stackTop = 0;
    int *stack = (int*)malloc(n * sizeof(int));
    stack[stackTop++] = 0;
    parent[0] = 0;
    int correctGuesses = 0;
    while (stackTop > 0) {
        int node = stack[--stackTop];
        for (int i = 0; i < adjSizes[node]; ++i) {
            int nei = adj[node][i];
            if (parent[nei] == -1) {
                parent[nei] = node;
                if (guessSet[(size_t)node * n + nei]) {
                    correctGuesses++;
                }
                stack[stackTop++] = nei;
            }
        }
    }

    /* Reroot and count possible roots */
    int result = 0;
    stackTop = 0;
    stack[stackTop++] = 0;
    memset(parent, -1, n * sizeof(int));
    parent[0] = 0;
    while (stackTop > 0) {
        int node = stack[--stackTop];
        if (correctGuesses >= k) {
            result++;
        }
        for (int i = 0; i < adjSizes[node]; ++i) {
            int nei = adj[node][i];
            if (parent[nei] == -1) {
                parent[nei] = node;
                /* adjust correct guesses when rerooting */
                if (guessSet[(size_t)node * n + nei]) {
                    correctGuesses--;
                }
                if (guessSet[(size_t)nei * n + node]) {
                    correctGuesses++;
                }
                stack[stackTop++] = nei;
            }
        }
    }
    /* free memory */
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    free(guessSet);
    free(parent);
    free(stack);
    return result;  
}
