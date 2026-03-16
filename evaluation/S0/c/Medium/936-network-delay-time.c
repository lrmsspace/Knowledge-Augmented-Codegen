// Source: https://leetcode.com/problems/network-delay-time/   |   Difficulty: Medium
//
// Problem Description:
// You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
//
// We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
//
// Example:
// Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// Output: 2
//
// Constraints:
// 1 <= k <= n <= 100
// 	1 <= times.length <= 6000
// 	times[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	0 <= wi <= 100
// 	All the pairs (ui, vi) are unique. (i.e., no multiple edges.)
//

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k){
    int graph[101][101];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = (i == j) ? 0 : 1e9;
        }
    }
    for (int i = 0; i < timesSize; i++) {
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        graph[u][v] = w;
    }

    for (int k_node = 1; k_node <= n; k_node++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (graph[i][j] > graph[i][k_node] + graph[k_node][j]) {
                    graph[i][j] = graph[i][k_node] + graph[k_node][j];
                }
            }
        }
    }

    int max_delay = 0;
    for (int i = 1; i <= n; i++) {
        if (graph[k][i] == 1e9) {
            return -1;
        }
        if (graph[k][i] > max_delay) {
            max_delay = graph[k][i];
        }
    }

    return max_delay;
}
