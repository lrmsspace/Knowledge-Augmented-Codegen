// Source: https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/   |   Difficulty: Hard
//
// Problem Description:
// There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively. You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
//
// You must connect one node from the first tree with another node from the second tree with an edge.
//
// Return the minimum possible diameter of the resulting tree.
//
// The diameter of a tree is the length of the longest path between any two nodes in the tree.
//
// Example:
// Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
//
// Output: 3
//
// Explanation:
//
// We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.
//
// Constraints:
// 1 <= n, m <= 105
// 	edges1.length == n - 1
// 	edges2.length == m - 1
// 	edges1[i].length == edges2[i].length == 2
// 	edges1[i] = [ai, bi]
// 	0 <= ai, bi < n
// 	edges2[i] = [ui, vi]
// 	0 <= ui, vi < m
// 	The input is generated such that edges1 and edges2 represent valid trees.
//

int minimumDiameterAfterMerge(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize) {
    typedef struct {
        int* neighbors;
        int neighborCount;
    } Node;

    Node* buildGraph(int** edges, int edgesSize, int* edgesColSize, int n) {
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
        return graph;
    }

    int bfs(Node* graph, int n, int start, int* farthestNode) {
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
                    dist[v] = dist[u] + 1;
                    queue[back++] = v;
                }
            }
        }

        int maxDist = 0;
        *farthestNode = start;
        for (int i = 0; i < n; i++) {
            if (dist[i] > maxDist) {
                maxDist = dist[i];
                *farthestNode = i;
            }
        }

        free(dist);
        free(queue);
        return maxDist;
    }

    int n1 = edges1Size + 1;
    Node* graph1 = buildGraph(edges1, edges1Size, edges1ColSize, n1);
    int farthestNode1;
    bfs(graph1, n1, 0, &farthestNode1);
    int diameter1 = bfs(graph1, n1, farthestNode1, &farthestNode1);
    for (int i = 0; i < n1; i++) {
        free(graph1[i].neighbors);
    }
    free(graph1);
    int n2 = edges2Size + 1;
    Node* graph2 = buildGraph(edges2, edges2Size, edges2ColSize, n2);
    int farthestNode2;
    bfs(graph2, n2, 0, &farthestNode2);
    int diameter2 = bfs(graph2, n2, farthestNode2, &farthestNode2);
    for (int i = 0; i < n2; i++) {
        free(graph2[i].neighbors);
    }
    free(graph2);
    int radius1 = (diameter1 + 1) / 2;
    int radius2 = (diameter2 + 1) / 2;
    int mergedDiameter = radius1 + radius2 + 1;
    int result = diameter1 > diameter2 ? diameter1 : diameter2;
    if (mergedDiameter > result) {
        result = mergedDiameter;
    }
    return result;
}
