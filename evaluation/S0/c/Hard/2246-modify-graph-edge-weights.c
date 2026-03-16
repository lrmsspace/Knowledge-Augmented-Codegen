// Source: https://leetcode.com/problems/modify-graph-edge-weights/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).
//
// Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2 * 109] so that the shortest distance between the nodes source and destination becomes equal to an integer target. If there are multiple modifications that make the shortest distance between source and destination equal to target, any of them will be considered correct.
//
// Return an array containing all edges (even unmodified ones) in any order if it is possible to make the shortest distance from source to destination equal to target, or an empty array if it's impossible.
//
// Note: You are not allowed to modify the weights of edges with initial positive weights.
//
// Example:
// Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
// Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
// Explanation: The graph above shows a possible modification to the edges, making the distance from 0 to 1 equal to 5.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 3
// 	0 <= ai, bi < n
// 	wi = -1 or 1 <= wi <= 107
// 	ai != bi
// 	0 <= source, destination < n
// 	source != destination
// 	1 <= target <= 109
// 	The graph is connected, and there are no self-loops or repeated edges
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define INF 1e18
#define MAX_N 105

typedef struct {
    int to;
    long long weight;
} Edge;

typedef struct {
    int node;
    long long dist;
} Item;

long long dijkstra(int n, int source, int destination, int** graph, int* graphSize) {
    long long* dist = (long long*)malloc(sizeof(long long) * n);
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[source] = 0;
    
    // Simple priority queue - using array
    Item* pq = (Item*)malloc(sizeof(Item) * (n * n + 10));
    int pqSize = 0;
    pq[pqSize++] = (Item){source, 0};
    
    while (pqSize > 0) {
        // Find minimum
        int minIdx = 0;
        for (int i = 1; i < pqSize; i++) {
            if (pq[i].dist < pq[minIdx].dist) {
                minIdx = i;
            }
        }
        
        Item cur = pq[minIdx];
        pq[minIdx] = pq[pqSize - 1];
        pqSize--;
        
        if (cur.dist > dist[cur.node]) continue;
        
        // Process neighbors
        for (int i = 0; i < graphSize[cur.node]; i++) {
            Edge* edge = (Edge*)((char*)graph[cur.node] + i * sizeof(Edge));
            int next = edge->to;
            long long newDist = cur.dist + edge->weight;
            
            if (newDist < dist[next]) {
                dist[next] = newDist;
                pq[pqSize++] = (Item){next, newDist};
            }
        }
    }
    
    long long result = dist[destination];
    free(dist);
    free(pq);
    return result;
}

int** modifiedGraphEdges(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination, int target, int* returnSize, int** returnColumnSizes) {
    // Build adjacency list with dynamic allocation
    Edge** graph = (Edge**)malloc(sizeof(Edge*) * n);
    int* graphSize = (int*)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++) {
        graph[i] = (Edge*)malloc(sizeof(Edge) * (edgesSize * 2));
        graphSize[i] = 0;
    }
    
    // Record which edges have -1 weight
    int negEdges[edgesSize];
    int negCount = 0;
    
    // Add edges to graph, use INF weight for -1 edges initially
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1];
        long long w = (edges[i][2] == -1) ? INF : edges[i][2];
        
        graph[u][graphSize[u]++] = (Edge){v, w};
        graph[v][graphSize[v]++] = (Edge){u, w};
        
        if (edges[i][2] == -1) {
            negEdges[negCount++] = i;
        }
    }
    
    // Try all combinations of -1 edge weights using recursion/backtracking
    // First, assign all -1 edges to 1
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][2] == -1) {
            edges[i][2] = 1;
        }
    }
    
    // Rebuild graph with weights=1 for -1 edges
    for (int i = 0; i < n; i++) {
        graphSize[i] = 0;
    }
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1];
        long long w = edges[i][2];
        
        graph[u][graphSize[u]++] = (Edge){v, w};
        graph[v][graphSize[v]++] = (Edge){u, w};
    }
    
    // Check initial shortest path with all -1 edges set to 1
    long long dist1 = dijkstra(n, source, destination, (int**)graph, graphSize);
    
    if (dist1 < target) {
        // Impossible
        int** result = (int**)malloc(sizeof(int*));
        *returnSize = 0;
        *returnColumnSizes = (int*)malloc(0);
        
        for (int i = 0; i < n; i++) {
            free(graph[i]);
        }
        free(graph);
        free(graphSize);
        
        return result;
    }
    
    // Increase one of the -1 edges by (dist1 - target)
    bool found = false;
    for (int i = 0; i < negCount && !found; i++) {
        int edgeIdx = negEdges[i];
        long long increase = dist1 - target;
        
        // Modify this edge
        long long oldWeight = edges[edgeIdx][2];
        edges[edgeIdx][2] = oldWeight + increase;
        
        // Rebuild graph
        for (int j = 0; j < n; j++) {
            graphSize[j] = 0;
        }
        
        for (int j = 0; j < edgesSize; j++) {
            int u = edges[j][0], v = edges[j][1];
            long long w = edges[j][2];
            
            graph[u][graphSize[u]++] = (Edge){v, w};
            graph[v][graphSize[v]++] = (Edge){u, w};
        }
        
        long long newDist = dijkstra(n, source, destination, (int**)graph, graphSize);
        
        if (newDist == target) {
            found = true;
        } else {
            edges[edgeIdx][2] = oldWeight;
        }
    }
    
    // Build result
    int** result = (int**)malloc(sizeof(int*) * edgesSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * edgesSize);
    
    for (int i = 0; i < edgesSize; i++) {
        result[i] = (int*)malloc(sizeof(int) * 3);
        result[i][0] = edges[i][0];
        result[i][1] = edges[i][1];
        result[i][2] = edges[i][2];
        (*returnColumnSizes)[i] = 3;
    }
    
    *returnSize = found ? edgesSize : 0;
    
    // Free memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphSize);
    
    if (!found) {
        for (int i = 0; i < edgesSize; i++) {
            free(result[i]);
        }
        free(result);
        free(*returnColumnSizes);
        result = (int**)malloc(sizeof(int*));
    }
    
    return result;
}