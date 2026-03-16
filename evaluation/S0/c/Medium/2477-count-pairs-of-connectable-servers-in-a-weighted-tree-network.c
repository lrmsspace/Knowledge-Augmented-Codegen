// Source: https://leetcode.com/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network/   |   Difficulty: Medium
//
// Problem Description:
// You are given an unrooted weighted tree with n vertices representing servers numbered from 0 to n - 1, an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional edge between vertices ai and bi of weight weighti. You are also given an integer signalSpeed.
//
// Two servers a and b are connectable through a server c if:
//
//
// 	a < b, a != c and b != c.
// 	The distance from c to a is divisible by signalSpeed.
// 	The distance from c to b is divisible by signalSpeed.
// 	The path from c to b and the path from c to a do not share any edges.
//
//
// Return an integer array count of length n where count[i] is the number of server pairs that are connectable through the server i.
//
// Example:
// Input: edges = [[0,1,1],[1,2,5],[2,3,13],[3,4,9],[4,5,2]], signalSpeed = 1
// Output: [0,4,6,6,4,0]
// Explanation: Since signalSpeed is 1, count[c] is equal to the number of pairs of paths that start at c and do not share any edges.
// In the case of the given path graph, count[c] is equal to the number of servers to the left of c multiplied by the servers to the right of c.
//
// Constraints:
// 2 <= n <= 1000
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ai, bi < n
// 	edges[i] = [ai, bi, weighti]
// 	1 <= weighti <= 106
// 	1 <= signalSpeed <= 106
// 	The input is generated such that edges represents a valid tree.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countPairsOfConnectableServers(int** edges, int edgesSize, int* edgesColSize, int signalSpeed, int* returnSize) {
    int n = edgesSize + 1;
    *returnSize = n;
    int* result = (int*)calloc(n, sizeof(int));
    
    // Build adjacency list
    typedef struct {
        int to;
        int weight;
        struct Node* next;
    } Node;
    
    Node** graph = (Node**)calloc(n, sizeof(Node*));
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        
        Node* nodeU = (Node*)malloc(sizeof(Node));
        nodeU->to = v;
        nodeU->weight = w;
        nodeU->next = graph[u];
        graph[u] = nodeU;
        
        Node* nodeV = (Node*)malloc(sizeof(Node));
        nodeV->to = u;
        nodeV->weight = w;
        nodeV->next = graph[v];
        graph[v] = nodeV;
    }
    
    // DFS function to calculate subtree sizes and count pairs
    int* subtreeSize = (int*)calloc(n, sizeof(int));
    
    void dfs(int u, int parent) {
        subtreeSize[u] = 1; // Count itself
        for (Node* curr = graph[u]; curr != NULL; curr = curr->next) {
            int v = curr->to;
            if (v == parent) continue;
            dfs(v, u);
            if (curr->weight % signalSpeed == 0) {
                result[u] += subtreeSize[v] * (n - subtreeSize[v]);
            }
            subtreeSize[u] += subtreeSize[v];
        }
    }
    
    dfs(0, -1);
    
    // Free memory
    for (int i = 0; i < n; i++) {
        Node* curr = graph[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph);
    free(subtreeSize);
    
    return result;      
}
