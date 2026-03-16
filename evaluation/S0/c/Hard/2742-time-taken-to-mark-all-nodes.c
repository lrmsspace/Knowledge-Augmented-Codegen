// Source: https://leetcode.com/problems/time-taken-to-mark-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
//
// Initially, all nodes are unmarked. For each node i:
//
//
// 	If i is odd, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 1.
// 	If i is even, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 2.
//
//
// Return an array times where times[i] is the time when all nodes get marked in the tree, if you mark node i at time t = 0.
//
// Note that the answer for each times[i] is independent, i.e. when you mark node i all other nodes are unmarked.
//
// Example:
// Input: edges = [[0,1],[0,2]]
//
// Output: [2,4,3]
//
// Explanation:
//
//
//
//
// 	For i = 0:
//
// 	
// 		Node 1 is marked at t = 1, and Node 2 at t = 2.
// 	
// 	
// 	For i = 1:
// 	
// 		Node 0 is marked at t = 2, and Node 2 at t = 4.
// 	
// 	
// 	For i = 2:
// 	
// 		Node 0 is marked at t = 2, and Node 1 at t = 3.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= edges[i][0], edges[i][1] <= n - 1
// 	The input is generated such that edges represents a valid tree.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* timeTaken(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    int n = edgesSize + 1;
    *returnSize = n;
    int* times = (int*)malloc(n * sizeof(int));
    if (!times) return NULL;

    typedef struct {
        int* neighbors;
        int neighborCount;
    } Node;

    Node* graph = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        graph[i].neighbors = NULL;
        graph[i].neighborCount = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u].neighbors = (int*)realloc(graph[u].neighbors, (graph[u].neighborCount + 1) * sizeof(int));
        graph[u].neighbors[graph[u].neighborCount++] = v;
        graph[v].neighbors = (int*)realloc(graph[v].neighbors, (graph[v].neighborCount + 1) * sizeof(int));
        graph[v].neighbors[graph[v].neighborCount++] = u;
    }

    for (int start = 0; start < n; start++) {
        int* dist = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) dist[i] = -1;
        dist[start] = 0;

        int* queue = (int*)malloc(n * sizeof(int));
        int front = 0, back = 0;
        queue[back++] = start;

        while (front < back) {
            int u = queue[front++];
            for (int i = 0; i < graph[u].neighborCount; i++) {
                int v = graph[u].neighbors[i];
                if (dist[v] == -1) {
                    dist[v] = dist[u] + ((v % 2 == 0) ? 2 : 1);
                    queue[back++] = v;
                }
            }
        }

        int maxTime = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i] > maxTime) {
                maxTime = dist[i];
            }
        }
        times[start] = maxTime;

        free(dist);
        free(queue);
    }

    for (int i = 0; i < n; i++) {
        free(graph[i].neighbors);
    }
    free(graph);
    return times;
}
