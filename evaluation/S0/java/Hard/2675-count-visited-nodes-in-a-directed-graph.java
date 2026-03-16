// Source: https://leetcode.com/problems/count-visited-nodes-in-a-directed-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a directed graph consisting of n nodes numbered from 0 to n - 1 and n directed edges.
//
// You are given a 0-indexed array edges where edges[i] indicates that there is an edge from node i to node edges[i].
//
// Consider the following process on the graph:
//
//
// 	You start from a node x and keep visiting other nodes through edges until you reach a node that you have already visited before on this same process.
//
//
// Return an array answer where answer[i] is the number of different nodes that you will visit if you perform the process starting from node i.
//
// Example:
// Input: edges = [1,2,0,0]
// Output: [3,3,3,4]
// Explanation: We perform the process starting from each node in the following way:
// - Starting from node 0, we visit the nodes 0 -> 1 -> 2 -> 0. The number of different nodes we visit is 3.
// - Starting from node 1, we visit the nodes 1 -> 2 -> 0 -> 1. The number of different nodes we visit is 3.
// - Starting from node 2, we visit the nodes 2 -> 0 -> 1 -> 2. The number of different nodes we visit is 3.
// - Starting from node 3, we visit the nodes 3 -> 0 -> 1 -> 2 -> 0. The number of different nodes we visit is 4.
//
// Constraints:
// n == edges.length
// 	2 <= n <= 105
// 	0 <= edges[i] <= n - 1
// 	edges[i] != i
//

class Solution {
    public int[] countVisitedNodes(List<Integer> edges) {
        int n = edges.size();
        int[] answer = new int[n];
        boolean[] visited = new boolean[n];

        for (int i = 0; i < n; i++) {
            if (answer[i] != 0) {
                continue;
            }

            List<Integer> path = new ArrayList<>();
            Set<Integer> inPath = new HashSet<>();
            int current = i;

            while (!visited[current]) {
                visited[current] = true;
                path.add(current);
                inPath.add(current);
                current = edges.get(current);

                if (answer[current] != 0) {
                    int count = answer[current];
                    for (int node : path) {
                        count++;
                        answer[node] = count;
                    }
                    break;
                }

                if (inPath.contains(current)) {
                    int cycleStartIndex = path.indexOf(current);
                    int cycleLength = path.size() - cycleStartIndex;

                    for (int j = cycleStartIndex; j < path.size(); j++) {
                        answer[path.get(j)] = cycleLength;
                    }

                    int count = cycleLength;
                    for (int j = cycleStartIndex - 1; j >= 0; j--) {
                        count++;
                        answer[path.get(j)] = count;
                    }
                    break;
                }
            }
        }

        return answer;          
    }
}
