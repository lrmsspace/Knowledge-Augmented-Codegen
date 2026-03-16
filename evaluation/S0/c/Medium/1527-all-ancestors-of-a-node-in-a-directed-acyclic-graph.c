// Source: https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n representing the number of nodes of a Directed Acyclic Graph (DAG). The nodes are numbered from 0 to n - 1 (inclusive).
//
// You are also given a 2D integer array edges, where edges[i] = [fromi, toi] denotes that there is a unidirectional edge from fromi to toi in the graph.
//
// Return a list answer, where answer[i] is the list of ancestors of the ith node, sorted in ascending order.
//
// A node u is an ancestor of another node v if u can reach v via a set of edges.
//
// Example:
// Input: n = 8, edgeList = [[0,3],[0,4],[1,3],[2,4],[2,7],[3,5],[3,6],[3,7],[4,6]]
// Output: [[],[],[],[0,1],[0,2],[0,1,3],[0,1,2,3,4],[0,1,2,3]]
// Explanation:
// The above diagram represents the input graph.
// - Nodes 0, 1, and 2 do not have any ancestors.
// - Node 3 has two ancestors 0 and 1.
// - Node 4 has two ancestors 0 and 2.
// - Node 5 has three ancestors 0, 1, and 3.
// - Node 6 has five ancestors 0, 1, 2, 3, and 4.
// - Node 7 has four ancestors 0, 1, 2, and 3.
//
// Constraints:
// 1 <= n <= 1000
// 	0 <= edges.length <= min(2000, n * (n - 1) / 2)
// 	edges[i].length == 2
// 	0 <= fromi, toi <= n - 1
// 	fromi != toi
// 	There are no duplicate edges.
// 	The graph is directed and acyclic.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** getAncestors(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize, int** returnColumnSizes) {
    // Adjacency list representation of the graph
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }

    // In-degree array
    int* inDegree = (int*)calloc(n, sizeof(int));

    // Build the graph and in-degree array
    for (int i = 0; i < edgesSize; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        graph[from][graphColSize[from]++] = to;
        inDegree[to]++;
    }

    // Ancestor sets
    int** ancestors = (int**)malloc(n * sizeof(int*));
    int* ancestorsColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        ancestors[i] = (int*)malloc(n * sizeof(int));
    }

    // Queue for topological sort
    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, rear = 0;

    // Enqueue nodes with in-degree 0
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // Topological sort and ancestor collection
    while (front < rear) {
        int node = queue[front++];
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];

            // Add current node as an ancestor of neighbor
            ancestors[neighbor][ancestorsColSize[neighbor]++] = node;

            // Add all ancestors of current node to neighbor
            for (int j = 0; j < ancestorsColSize[node]; j++) {
                ancestors[neighbor][ancestorsColSize[neighbor]++] = ancestors[node][j];
            }

            // Decrease in-degree and enqueue if it becomes 0
            if (--inDegree[neighbor] == 0) {
                queue[rear++] = neighbor;
            }
        }
    }

    // Prepare the result
    *returnSize = n;  
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        // Sort ancestors and remove duplicates
        int size = ancestorsColSize[i];
        qsort(ancestors[i], size, sizeof(int), (int (*)(const void*, const void*))strcmp);
        int uniqueSize = 0;
        for (int j = 0; j < size; j++) {
            if (j == 0 || ancestors[i][j] != ancestors[i][j - 1]) {
                ancestors[i][uniqueSize++] = ancestors[i][j];
            }
        }

        // Allocate result array for node i
        result[i] = (int*)malloc(uniqueSize * sizeof(int));
        memcpy(result[i], ancestors[i], uniqueSize * sizeof(int));
        (*returnColumnSizes)[i] = uniqueSize;
    }
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
        free(ancestors[i]);
    }
    free(graph);
    free(graphColSize);
    free(inDegree);
    free(ancestors);
    free(queue);
    return result;
}
