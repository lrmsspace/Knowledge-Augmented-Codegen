// Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
//
// You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
//
// Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
//
// The degree of a node is the number of edges connected to it.
//
// Example:
// Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
// Output: true
// Explanation: The above diagram shows a valid way of adding an edge.
// Every node in the resulting graph is connected to an even number of edges.
//
// Constraints:
// 3 <= n <= 105
// 	2 <= edges.length <= 105
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There are no repeated edges.
//

class Solution {
    public boolean isPossible(int n, List<List<Integer>> edges) {
        int[] degree = new int[n + 1];
        Set<String> edgeSet = new HashSet<>();

        for (List<Integer> edge : edges) {
            int u = edge.get(0);
            int v = edge.get(1);
            degree[u]++;
            degree[v]++;
            String edgeKey = u < v ? u + "," + v : v + "," + u;
            edgeSet.add(edgeKey);
        }

        List<Integer> oddDegreeNodes = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            if (degree[i] % 2 != 0) {
                oddDegreeNodes.add(i);
            }
        }

        int oddCount = oddDegreeNodes.size();
        if (oddCount == 0) {
            return true;
        } else if (oddCount == 2) {
            int u = oddDegreeNodes.get(0);
            int v = oddDegreeNodes.get(1);
            String edgeKey = u < v ? u + "," + v : v + "," + u;
            return !edgeSet.contains(edgeKey);
        } else if (oddCount == 4) {
            for (int i = 0; i < 4; i++) {
                for (int j = i + 1; j < 4; j++) {
                    int a = oddDegreeNodes.get(i);
                    int b = oddDegreeNodes.get(j);
                    String edgeKey = a < b ? a + "," + b : b + "," + a;
                    if (edgeSet.contains(edgeKey)) {
                        continue;
                    }
                    List<Integer> remaining = new ArrayList<>();
                    for (int k = 0; k < 4; k++) {
                        if (k != i && k != j) {
                            remaining.add(oddDegreeNodes.get(k));
                        }
                    }
                    int c = remaining.get(0);
                    int d = remaining.get(1);
                    String edgeKey2 = c < d ? c + "," + d : d + "," + c;
                    if (!edgeSet.contains(edgeKey2)) {
                        return true;
                    }
                }
            }
            return false;
        } else {
            return false;
        }           
    }
}
