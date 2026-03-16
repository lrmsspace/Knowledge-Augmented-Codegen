// Source: https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/   |   Difficulty: Hard
//
// Problem Description:
// You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.
//
// You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.
//
// Divide the nodes of the graph into m groups (1-indexed) such that:
//
//
// 	Each node in the graph belongs to exactly one group.
// 	For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
//
//
// Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
// Output: 4
// Explanation: As shown in the image we:
// - Add node 5 to the first group.
// - Add node 1 to the second group.
// - Add nodes 2 and 4 to the third group.
// - Add nodes 3 and 6 to the fourth group.
// We can see that every edge is satisfied.
// It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.
//
// Constraints:
// 1 <= n <= 500
// 	1 <= edges.length <= 104
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There is at most one edge between any pair of vertices.
//

class Solution {
public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n + 1, false);
        int result = 0;
        
        for (int i = 1; i <= n; ++i) {
            if (visited[i]) continue;
            
            queue<int> q;
            q.push(i);
            visited[i] = true;
            int componentMaxDepth = 0;
            int nodesInComponent = 0;
            
            while (!q.empty()) {
                int size = q.size();
                componentMaxDepth++;
                
                for (int j = 0; j < size; ++j) {
                    int node = q.front();
                    q.pop();
                    nodesInComponent++;
                    
                    for (int neighbor : graph[node]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
            
            if (nodesInComponent < componentMaxDepth) {
                return -1;
            }
            
            result += componentMaxDepth;
        }
        
        return result;          
    }
};
