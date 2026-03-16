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
// - Finding the Eulerian path in O(M) (graph, eulerian-circuit, dfs)
//   • When to use: Use when you need to find a path or cycle that traverses every edge exactly once in a given graph. It's applicable when specific vertex degree conditions are met for path or cycle existence.
//   • Idea: This algorithm constructs an Eulerian path or cycle by first verifying vertex degree conditions and graph connectivity, then performing a recursive DFS-like traversal to build the path. It achieves a time complexity of O(M), where M is the number of edges.
//   • Invariants: Every edge in the constructed path has been traversed exactly once.; All edges incident to the current vertex have been explored or are part of the remaining graph.
//   • Tips: Verify graph connectivity, ignoring isolated vertices.; For an Eulerian path, ensure exactly two vertices have odd degrees.
//   • Pitfalls: Failing to check graph connectivity before starting.; Incorrectly counting odd degree vertices for path vs. cycle.
// - Search for connected components in a graph (stack, graph, dfs, recursion)
//   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
//   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
//   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
//   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
//   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** validArrangement(int** pairs, int pairsSize, int* pairsColSize, int* returnSize, int** returnColumnSizes) {
    /* Build graph and in/out degree maps */
    #define MAX_NODES 200000
    typedef struct Edge {
        int to;
        struct Edge* next;
    } Edge;

    Edge* graph[MAX_NODES] = {0};
    int outDegree[MAX_NODES] = {0};
    int inDegree[MAX_NODES] = {0};
    int nodeExists[MAX_NODES] = {0};

    for (int i = 0; i < pairsSize; i++) {
        int u = pairs[i][0];
        int v = pairs[i][1];

        Edge* edge = (Edge*)malloc(sizeof(Edge));
        edge->to = v;
        edge->next = graph[u];
        graph[u] = edge;

        outDegree[u]++;
        inDegree[v]++;
        nodeExists[u] = 1;
        nodeExists[v] = 1;
    }

    /* Find start node for Eulerian path */
    int startNode = -1;
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodeExists[i]) {
            if (outDegree[i] - inDegree[i] == 1) {
                startNode = i;
                break;
            }
        }
    }
    if (startNode == -1) {
        for (int i = 0; i < MAX_NODES; i++) {
            if (nodeExists[i]) {
                startNode = i;
                break;
            }
        }
    }

    /* Hierholzer's algorithm for Eulerian path */
    int* stack = (int*)malloc(pairsSize * sizeof(int));
    int stackSize = 0;
    int* result = (int*)malloc(pairsSize * 2 * sizeof(int));
    int resultSize = 0;

    stack[stackSize++] = startNode;

    while (stackSize > 0) {
        int u = stack[--stackSize];
        while (graph[u]) {
            Edge* edge = graph[u];
            graph[u] = edge->next;
            stack[stackSize++] = edge->to;
            free(edge);
            u = stack[--stackSize];
        }
        result[resultSize++] = u;
    }

    /* Prepare return value */
    *returnSize = pairsSize;
    *returnColumnSizes = (int*)malloc(pairsSize * sizeof(int));
    int** arrangedPairs = (int**)malloc(pairsSize * sizeof(int*));
    for (int i = 0; i < pairsSize; i++) {
        arrangedPairs[i] = (int*)malloc(2 * sizeof(int));
        arrangedPairs[i][0] = result[pairsSize - i];
        arrangedPairs[i][1] = result[pairsSize - i - 1];
        (*returnColumnSizes)[i] = 2;
    }
    free(stack);
    free(result);
    return arrangedPairs;
}
