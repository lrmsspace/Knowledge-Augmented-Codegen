// Source: https://leetcode.com/problems/critical-connections-in-a-network/   |   Difficulty: Hard
//
// Problem Description:
// There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
//
// A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
//
// Return all critical connections in the network in any order.
//
// Example:
// Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
// Output: [[1,3]]
// Explanation: [[3,1]] is also accepted.
//
// Constraints:
// 2 <= n <= 105
// 	n - 1 <= connections.length <= 105
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated connections.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** criticalConnections(int n, int** connections, int connectionsSize, int* connectionsColSize, int* returnSize, int** returnColumnSizes) {
   
    #define MAX_NODES 100000
    #define MAX_EDGES 200000

    typedef struct {
        int to;
        struct Edge* next;
    } Edge;

    Edge* graph[MAX_NODES];
    int disc[MAX_NODES], low[MAX_NODES], time = 0;
    int** result = (int**)malloc(sizeof(int*) * connectionsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * connectionsSize);
    *returnSize = 0;

    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
        disc[i] = -1;
        low[i] = -1;
    }

    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];

        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = v;
        edge1->next = graph[u];
        graph[u] = edge1;

        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = u;
        edge2->next = graph[v];
        graph[v] = edge2;
    }

    void dfs(int u, int parent) {
        disc[u] = low[u] = time++;
        for (Edge* edge = graph[u]; edge != NULL; edge = edge->next) {
            int v = edge->to;
            if (disc[v] == -1) {
                dfs(v, u);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];
                if (low[v] > disc[u]) {
                    result[*returnSize] = (int*)malloc(2 * sizeof(int));
                    result[*returnSize][0] = u;
                    result[*returnSize][1] = v;
                    (*returnColumnSizes)[*returnSize] = 2;
                    (*returnSize)++;
                }
            } else if (v != parent) {
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            dfs(i, -1);
        }
    }

    return result;
}
