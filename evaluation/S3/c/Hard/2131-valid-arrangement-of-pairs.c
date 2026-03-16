// Source: https://leetcode.com/problems/valid-arrangement-of-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.
//
// Return any valid arrangement of pairs.
//
// Note: The inputs will be generated such that there exists a valid arrangement of pairs.
//
// Example:
// Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
// Output: [[11,9],[9,4],[4,5],[5,1]]
// Explanation:
// This is a valid arrangement since endi-1 always equals starti.
// end0 = 9 == 9 = start1 
// end1 = 4 == 4 = start2
// end2 = 5 == 5 = start3
//
// Constraints:
// 1 <= pairs.length <= 105
// 	pairs[i].length == 2
// 	0 <= starti, endi <= 109
// 	starti != endi
// 	No two pairs are exactly the same.
// 	There exists a valid arrangement of pairs.
//
// Helpful references (internal KB):
// - Strongly connected components and the condensation graph (graph, enumeration)
//   • When to use: When you need to identify maximal subgraphs where all vertices are mutually reachable, or to simplify a directed graph into a Directed Acyclic Graph (DAG) of components for further processing.
//   • Idea: This concept defines SCCs as maximal vertex subsets in a directed graph where all pairs are mutually reachable. It also introduces the condensation graph, which represents SCCs as nodes and forms a DAG, typically found in O(V+E) time.
//   • Invariants: Every vertex belongs to exactly one strongly connected component.; Within any SCC, a path exists from any vertex u to any other vertex v, and vice-versa.
//   • Tips: Understand that SCCs partition the graph's vertices.; The condensation graph is always a Directed Acyclic Graph (DAG).
//   • Pitfalls: Confusing SCCs with simple cycles or connected components in undirected graphs.; Incorrectly assuming the condensation graph has cycles.
// - Directed Graphs (graph, array, dfs, bfs)
//   • When to use: Use when modeling relationships with a specific flow direction between entities. It is ideal for determining reachability or finding paths from one or more sources.
//   • Idea: Directed graphs represent connections where edges have a specific direction, often implemented using adjacency lists. Depth-first search (DFS) and breadth-first search (BFS) are fundamental algorithms for traversing these graphs to find paths and determine reachability in O(V+E) time.
//   • Invariants: The 'visited' set accurately reflects all nodes for which traversal has been initiated.; For DFS, all nodes reachable from the current node via unvisited paths will eventually be explored.
//   • Tips: Always use a 'visited' set or array to prevent infinite loops in cycles and redundant processing.; Adjacency list representation is generally preferred for sparse graphs due to better space and time complexity for traversal.
//   • Pitfalls: Forgetting to handle cycles can lead to infinite loops or stack overflows in DFS.; Incorrectly applying algorithms designed for undirected graphs to directed graphs without modification.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** validArrangement(int** pairs, int pairsSize, int* pairsColSize, int* returnSize, int** returnColumnSizes) {
    int m = pairsSize;
    int* inDegree = (int*)malloc(100001u * sizeof(int));
    int* outDegree = (int*)malloc(100001u * sizeof(int));
    int** graph = (int**)malloc(100001u * sizeof(int*));
    int* graphSizes = (int*)malloc(100001u * sizeof(int));
    int** result = (int**)malloc((size_t)m * sizeof(int*));
    int* resultColSizes = (int*)malloc((size_t)m * sizeof(int));
    int i;

    (void)pairsColSize;

    if (!inDegree || !outDegree || !graph || !graphSizes || !result || !resultColSizes) {
        free(inDegree);
        free(outDegree);
        free(graph);
        free(graphSizes);
        free(result);
        free(resultColSizes);
        *returnSize = 0;
        return NULL;
    }

    for (i = 0; i < 100001; ++i) {
        inDegree[i] = 0;
        outDegree[i] = 0;
        graph[i] = NULL;
        graphSizes[i] = 0;
    }

    for (i = 0; i < m; ++i) {
        int u = pairs[i][0];
        int v = pairs[i][1];

        outDegree[u]++;
        inDegree[v]++;
    }

    for (i = 0; i < m; ++i) {
        int u = pairs[i][0];
        int v = pairs[i][1];

        graph[u] = (int*)realloc(graph[u], (size_t)outDegree[u] * sizeof(int));
        graph[u][--outDegree[u]] = v;
        graph[v] = (int*)realloc(graph[v], (size_t)inDegree[v] * sizeof(int));
        graph[v][--inDegree[v]] = u;
    }

    int start = 0;
    for (i = 0; i < 100001; ++i) {
        if (outDegree[i] > inDegree[i]) {
            start = i;
            break;
        }
    }
    
    int* stack = (int*)malloc((size_t)m * sizeof(int));
    int stackSize = 0;
    stack[stackSize++] = start;

    while (stackSize > 0) {
        int current = stack[stackSize - 1];
        if (graphSizes[current] > 0) {
            int next = graph[current][--graphSizes[current]];
            stack[stackSize++] = next;
        } else {
            result[--stackSize] = pairs[current];
            resultColSizes[stackSize] = 2;
        }
    }

    *returnSize = m;
    *returnColumnSizes = resultColSizes;
    free(stack);
    free(inDegree);
    free(outDegree);
    for (i = 0; i < 100001; ++i) {
        free(graph[i]);
    }
    free(graph);
    free(graphSizes);
    return result;
}
