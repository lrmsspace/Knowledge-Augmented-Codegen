// Source: https://leetcode.com/problems/possible-bipartition/   |   Difficulty: Medium
//
// Problem Description:
// We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.
//
// Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.
//
// Example:
// Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
// Output: true
// Explanation: The first group has [1,4], and the second group has [2,3].
//
// Constraints:
// 1 <= n <= 2000
// 	0 <= dislikes.length <= 104
// 	dislikes[i].length == 2
// 	1 <= ai < bi <= n
// 	All the pairs of dislikes are unique.
//

bool possibleBipartition(int n, int** dislikes, int dislikesSize, int* dislikesColSize) {
    int graph[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < dislikesSize; i++) {
        int a = dislikes[i][0];
        int b = dislikes[i][1];
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    int color[n + 1];
    for (int i = 0; i <= n; i++) {
        color[i] = -1;
    }

    for (int start = 1; start <= n; start++) {
        if (color[start] != -1) continue;

        color[start] = 0;
        int queue[n + 1];
        int front = 0, back = 0;
        queue[back++] = start;

        while (front < back) {
            int node = queue[front++];
            for (int neighbor = 1; neighbor <= n; neighbor++) {
                if (graph[node][neighbor]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];
                        queue[back++] = neighbor;
                    } else if (color[neighbor] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }

    return true;        
}
