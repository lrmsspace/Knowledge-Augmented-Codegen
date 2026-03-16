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

class Solution {
    public int[] countPairsOfConnectableServers(int[][] edges, int signalSpeed) {
        int n = edges.length + 1;
        List<int[]>[] graph = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            graph[edge[0]].add(new int[]{edge[1], edge[2]});
            graph[edge[1]].add(new int[]{edge[0], edge[2]});
        }

        int[] result = new int[n];

        for (int server = 0; server < n; server++) {
            List<Integer> subtreeSizes = new ArrayList<>();
            boolean[] visited = new boolean[n];
            visited[server] = true;

            for (int[] neighbor : graph[server]) {
                int neighborServer = neighbor[0];
                int weight = neighbor[1];
                if (!visited[neighborServer] && weight % signalSpeed == 0) {
                    int size = dfs(graph, neighborServer, visited, signalSpeed);
                    subtreeSizes.add(size);
                }
            }

            int totalSize = subtreeSizes.stream().mapToInt(Integer::intValue).sum();
            for (int size : subtreeSizes) {
                totalSize -= size;
                result[server] += size * totalSize;
            }
        }

        return result;          
    }
}
