// Source: https://leetcode.com/problems/count-valid-paths-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
//
// Return the number of valid paths in the tree.
//
// A path (a, b) is valid if there exists exactly one prime number among the node labels in the path from a to b.
//
// Note that:
//
//
// 	The path (a, b) is a sequence of distinct nodes starting with node a and ending with node b such that every two adjacent nodes in the sequence share an edge in the tree.
// 	Path (a, b) and path (b, a) are considered the same and counted only once.
//
// Example:
// Input: n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
// Output: 4
// Explanation: The pairs with exactly one prime number on the path between them are: 
// - (1, 2) since the path from 1 to 2 contains prime number 2. 
// - (1, 3) since the path from 1 to 3 contains prime number 3.
// - (1, 4) since the path from 1 to 4 contains prime number 2.
// - (2, 4) since the path from 2 to 4 contains prime number 2.
// It can be shown that there are only 4 valid paths.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	The input is generated such that edges represent a valid tree.
//

long long countPaths(int n, int** edges, int edgesSize, int* edgesColSize) {
    /* Sieve of Eratosthenes to find primes up to n */
    bool *isPrime = (bool*)malloc((n + 1) * sizeof(bool));
    for (int i = 0; i <= n; i++) isPrime[i] = true;
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    /* Build adjacency list */
    int **graph = (int**)malloc((n + 1) * sizeof(int*));
    int *graphSizes = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][graphSizes[u]++] = v;
        graph[v][graphSizes[v]++] = u;
    }

    long long result = 0;

    /* DFS to count valid paths */
    void dfs(int node, int parent, int primeCount, int *subtreeSize) {
        subtreeSize[node] = 1;
        for (int i = 0; i < graphSizes[node]; i++) {
            int neighbor = graph[node][i];
            if (neighbor != parent) {
                dfs(neighbor, node, primeCount + isPrime[neighbor], subtreeSize);
                if (isPrime[node]) {
                    result += subtreeSize[neighbor];
                } else if (isPrime[neighbor]) {
                    result += subtreeSize[neighbor];
                }
                subtreeSize[node] += subtreeSize[neighbor];
            }
        }
    }

    int *subtreeSize = (int*)calloc(n + 1, sizeof(int));
    dfs(1, -1, isPrime[1], subtreeSize);

    free(isPrime);
    for (int i = 0; i <= n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphSizes);
    free(subtreeSize);
    return result;
}
