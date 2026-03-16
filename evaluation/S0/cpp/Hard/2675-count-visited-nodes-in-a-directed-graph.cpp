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
public:
    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();
        vector<int> answer(n, 0);
        vector<int> state(n, 0);  // 0: unvisited, 1: visiting, 2: visited
        
        function<int(int)> dfs = [&](int node) {
            if (state[node] == 2) {
                return answer[node];
            }
            if (state[node] == 1) {
                // Cycle detected
                int cycleNode = node;
                int cycleSize = 1;
                int nextNode = edges[node];
                while (nextNode != cycleNode) {
                    cycleSize++;
                    nextNode = edges[nextNode];
                }
                
                // Mark all nodes in the cycle
                nextNode = edges[node];
                while (nextNode != cycleNode) {
                    answer[nextNode] = cycleSize;
                    state[nextNode] = 2;
                    nextNode = edges[nextNode];
                }
                answer[cycleNode] = cycleSize;
                state[cycleNode] = 2;
                
                return cycleSize;
            }
            
            state[node] = 1;  // Mark as visiting
            int nextNode = edges[node];
            int count = dfs(nextNode) + 1;
            answer[node] = count;
            state[node] = 2;  // Mark as visited
            
            return count;
        };
        
        for (int i = 0; i < n; i++) {
            if (state[i] == 0) {
                dfs(i);
            }
        }
        
        return answer;          
    }
};
