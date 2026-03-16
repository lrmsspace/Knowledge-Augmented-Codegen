// Source: https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.
//
// A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.
//
// The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.
//
// Return the number of restricted paths from node 1 to node n. Since that number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
// Output: 3
// Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
// 1) 1 --> 2 --> 5
// 2) 1 --> 2 --> 3 --> 5
// 3) 1 --> 3 --> 5
//
// Constraints:
// 1 <= n <= 2 * 104
// 	n - 1 <= edges.length <= 4 * 104
// 	edges[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= weighti <= 105
// 	There is at most one edge between any two nodes.
// 	There is at least one path between any two nodes.
//

int countRestrictedPaths(int n, int** edges, int edgesSize, int* edgesColSize) {
    #define MOD 1000000007
    #define MAXN 20010
    #define MAXE 40010
    #define INF 0x3f3f3f3f

    typedef struct {
        int to;
        int weight;
        int next;
    } Edge;

    Edge edge[MAXE * 2];
    int head[MAXN], edgeCount = 0;

    void addEdge(int u, int v, int w) {
        edge[edgeCount].to = v;
        edge[edgeCount].weight = w;
        edge[edgeCount].next = head[u];
        head[u] = edgeCount++;
    }

    // Dijkstra's algorithm to find shortest paths from node n
    int dist[MAXN];
    int visited[MAXN];

    typedef struct {
        int node;
        int dist;
    } Node;

    Node heap[MAXN];
    int heapSize = 0;

    void push(Node nd) {
        heap[heapSize++] = nd;
        int idx = heapSize - 1;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[parent].dist <= heap[idx].dist) break;
            Node temp = heap[parent];
            heap[parent] = heap[idx];
            heap[idx] = temp;
            idx = parent;
        }
    }

    Node pop() {
        Node ret = heap[0];
        heap[0] = heap[--heapSize];
        int idx = 0;
        while (true) {
            int left = idx * 2 + 1, right = idx * 2 + 2, smallest = idx;
            if (left < heapSize && heap[left].dist < heap[smallest].dist) smallest = left;
            if (right < heapSize && heap[right].dist < heap[smallest].dist) smallest = right;
            if (smallest == idx) break;
            Node temp = heap[smallest];
            heap[smallest] = heap[idx];
            heap[idx] = temp;
            idx = smallest;
        }
        return ret;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[n] = 0;
    push((Node){n, 0});
    while (heapSize) {
        Node curr = pop();
        int u = curr.node;
        if (visited[u]) continue;
        visited[u] = 1;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            int w = edge[i].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                push((Node){v, dist[v]});
            }
        }
    }
    // Count restricted paths using DP
    int dp[MAXN];
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
    }
    dp[n] = 1;
    typedef struct {
        int node;
        int dist;
    } NodeDist;
    NodeDist nodes[MAXN];
    for (int i = 1; i <= n; i++) {
        nodes[i - 1].node = i;
        nodes[i - 1].dist = dist[i];
    }
    // Sort nodes by distance
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (nodes[j].dist > nodes[j + 1].dist) {
                NodeDist temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int u = nodes[i].node;
        for (int j = head[u]; j != -1; j = edge[j].next) {
            int v = edge[j].to;
            if (dist[u] > dist[v]) {
                dp[u] = (dp[u] + dp[v]) % MOD;
            }
        }
    }
    return dp[1];
}
