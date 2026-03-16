// Source: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/   |   Difficulty: Medium
//
// Problem Description:
// You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.
//
// You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel. You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.
//
// Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
// Output: 4
// Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
// The four ways to get there in 7 minutes are:
// - 0 ➝ 6
// - 0 ➝ 4 ➝ 6
// - 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
// - 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6
//
// Constraints:
// 1 <= n <= 200
// 	n - 1 <= roads.length <= n * (n - 1) / 2
// 	roads[i].length == 3
// 	0 <= ui, vi <= n - 1
// 	1 <= timei <= 109
// 	ui != vi
// 	There is at most one road connecting any two intersections.
// 	You can reach any intersection from any other intersection.
//

int countPaths(int n, int** roads, int roadsSize, int* roadsColSize) {
    #define MOD 1000000007
    #define MAXN 200
    #define MAXE 40000
    typedef struct { int to, time, next; } Edge;
    
    Edge edges[MAXE];
    int head[MAXN], edgeCount = 0;
    
    void addEdge(int u, int v, int time) {
        edges[edgeCount] = (Edge){v, time, head[u]};
        head[u] = edgeCount++;
    }
    
    for (int i = 0; i < n; i++) head[i] = -1;
    
    for (int i = 0; i < roadsSize; i++) {
        int u = roads[i][0], v = roads[i][1], time = roads[i][2];
        addEdge(u, v, time);
        addEdge(v, u, time);
    }
    
    typedef struct { long long dist; int ways; } NodeInfo;
    NodeInfo nodeInfo[MAXN];
    
    for (int i = 0; i < n; i++) {
        nodeInfo[i].dist = __LONG_LONG_MAX__;
        nodeInfo[i].ways = 0;
    }
    
    nodeInfo[0].dist = 0;
    nodeInfo[0].ways = 1;
    
    typedef struct { int node; long long dist; } HeapNode;
    
    HeapNode heap[MAXN * MAXN];
    int heapSize = 0;
    
    void push(int node, long long dist) {
        heap[heapSize++] = (HeapNode){node, dist};
        int idx = heapSize - 1;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[parent].dist <= heap[idx].dist) break;
            HeapNode temp = heap[parent];
            heap[parent] = heap[idx];
            heap[idx] = temp;
            idx = parent;
        }
    }
    
    HeapNode pop() {
        HeapNode ret = heap[0];
        heap[0] = heap[--heapSize];
        int idx = 0;
        while (idx * 2 + 1 < heapSize) {
            int left = idx * 2 + 1;
            int right = idx * 2 + 2;
            int smallest = left;
            if (right < heapSize && heap[right].dist < heap[left].dist) {
                smallest = right;
            }
            if (heap[idx].dist <= heap[smallest].dist) break;
            HeapNode temp = heap[idx];
            heap[idx] = heap[smallest];
            heap[smallest] = temp;
            idx = smallest;
        }
        return ret;
    }
    push(0, 0);
    while (heapSize > 0) {
        HeapNode curr = pop();
        int u = curr.node;
        long long currDist = curr.dist;
        if (currDist > nodeInfo[u].dist) continue;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            long long time = edges[i].time;
            if (nodeInfo[u].dist + time < nodeInfo[v].dist) {
                nodeInfo[v].dist = nodeInfo[u].dist + time;
                nodeInfo[v].ways = nodeInfo[u].ways;
                push(v, nodeInfo[v].dist);
            } else if (nodeInfo[u].dist + time == nodeInfo[v].dist) {
                nodeInfo[v].ways = (nodeInfo[v].ways + nodeInfo[u].ways) % MOD;
            }
        }
    }
    return nodeInfo[n - 1].ways;
}
