// Source: https://leetcode.com/problems/critical-connections-in-a-network/   |   Difficulty: Hard
//
// Problem Description:
// There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
//
// A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
//
// Return all critical connections in the network in any order.
//
// Example:
// Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
// Output: [[1,3]]
// Explanation: [[3,1]] is also accepted.
//
// Constraints:
// 2 <= n <= 105
// 	n - 1 <= connections.length <= 105
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated connections.
//

class Solution {
    public List<List<Integer>> criticalConnections(int n, List<List<Integer>> connections) {
        List<List<Integer>> result = new ArrayList<>();
        Map<Integer, List<Integer>> graph = new HashMap<>();
        for (List<Integer> conn : connections) {
            graph.computeIfAbsent(conn.get(0), k -> new ArrayList<>()).add(conn.get(1));
            graph.computeIfAbsent(conn.get(1), k -> new ArrayList<>()).add(conn.get(0));
        }

        int[] ids = new int[n];
        int[] low = new int[n];
        boolean[] visited = new boolean[n];
        int[] id = {0};

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, -1, graph, ids, low, visited, id, result);
            }
        }

        return result;                  
    }
}
