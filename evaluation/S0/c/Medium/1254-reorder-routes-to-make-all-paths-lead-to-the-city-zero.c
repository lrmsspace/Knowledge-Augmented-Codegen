// Source: https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/   |   Difficulty: Medium
//
// Problem Description:
// There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is only one way to travel between two different cities (this network form a tree). Last year, The ministry of transport decided to orient the roads in one direction because they are too narrow.
//
// Roads are represented by connections where connections[i] = [ai, bi] represents a road from city ai to city bi.
//
// This year, there will be a big event in the capital (city 0), and many people want to travel to this city.
//
// Your task consists of reorienting some roads such that each city can visit the city 0. Return the minimum number of edges changed.
//
// It's guaranteed that each city can reach city 0 after reorder.
//
// Example:
// Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
// Output: 3
// Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).
//
// Constraints:
// 2 <= n <= 5 * 104
// 	connections.length == n - 1
// 	connections[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
//

int minReorder(int n, int** connections, int connectionsSize, int* connectionsColSize) {
    // Create an adjacency list to represent the graph
    typedef struct Edge {
        int to;
        int reversed; // 0 if original direction, 1 if reversed
        struct Edge* next;
    } Edge;

    Edge** graph = (Edge**)calloc(n, sizeof(Edge*));

    for (int i = 0; i < connectionsSize; i++) {
        int a = connections[i][0];
        int b = connections[i][1];

        // Original direction a -> b
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = b;
        edge1->reversed = 0;
        edge1->next = graph[a];
        graph[a] = edge1;

        // Reverse direction b -> a
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = a;
        edge2->reversed = 1;
        edge2->next = graph[b];
        graph[b] = edge2;
    }

    // DFS to count the number of edges to be reversed
    int* visited = (int*)calloc(n, sizeof(int));
    int result = 0;

    void dfs(int node) {
        visited[node] = 1;
        Edge* edge = graph[node];
        while (edge) {
            if (!visited[edge->to]) {
                result += edge->reversed; // Count if the edge is in original direction
                dfs(edge->to);
            }
            edge = edge->next;
        }
    }

    dfs(0);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        Edge* edge = graph[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph);
    free(visited);

    return result;      
}
