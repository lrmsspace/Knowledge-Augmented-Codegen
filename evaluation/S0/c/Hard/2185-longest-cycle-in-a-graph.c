// Source: https://leetcode.com/problems/longest-cycle-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.
//
// The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. If there is no outgoing edge from node i, then edges[i] == -1.
//
// Return the length of the longest cycle in the graph. If no cycle exists, return -1.
//
// A cycle is a path that starts and ends at the same node.
//
// Example:
// Input: edges = [3,3,4,2,3]
// Output: 3
// Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
// The length of this cycle is 3, so 3 is returned.
//
// Constraints:
// n == edges.length
// 	2 <= n <= 105
// 	-1 <= edges[i] < n
// 	edges[i] != i
//

int longestCycle(int* edges, int edgesSize) {
    int *visited = (int*)calloc(edgesSize, sizeof(int));
    if (!visited) return -1;

    int longest = -1;
    for (int i = 0; i < edgesSize; ++i) {
        if (visited[i]) continue;

        int step = 1;
        int curr = i;
        int *stepMap = (int*)calloc(edgesSize, sizeof(int));
        if (!stepMap) {
            free(visited);
            return -1;
        }

        while (curr != -1 && !visited[curr]) {
            visited[curr] = 1;
            stepMap[curr] = step++;
            curr = edges[curr];
            if (curr != -1 && stepMap[curr] != 0) {
                int cycleLen = step - stepMap[curr];
                if (cycleLen > longest) longest = cycleLen;
                break;
            }
        }
        free(stepMap);
    }

    free(visited);
    return longest;     
}
