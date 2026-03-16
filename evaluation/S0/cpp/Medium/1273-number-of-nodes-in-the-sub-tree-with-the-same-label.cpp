// Source: https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/   |   Difficulty: Medium
//
// Problem Description:
// You are given a tree (i.e. a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. The root of the tree is the node 0, and each node of the tree has a label which is a lower-case character given in the string labels (i.e. The node with the number i has the label labels[i]).
//
// The edges array is given on the form edges[i] = [ai, bi], which means there is an edge between nodes ai and bi in the tree.
//
// Return an array of size n where ans[i] is the number of nodes in the subtree of the ith node which have the same label as node i.
//
// A subtree of a tree T is the tree consisting of a node in T and all of its descendant nodes.
//
// Example:
// Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], labels = "abaedcd"
// Output: [2,1,1,1,1,1,1]
// Explanation: Node 0 has label 'a' and its sub-tree has node 2 with label 'a' as well, thus the answer is 2. Notice that any node is part of its sub-tree.
// Node 1 has a label 'b'. The sub-tree of node 1 contains nodes 1,4 and 5, as nodes 4 and 5 have different labels than node 1, the answer is just 1 (the node itself).
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	labels.length == n
// 	labels is consisting of only of lowercase English letters.
//

class Solution {
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> result(n, 0);
        vector<bool> visited(n, false);

        function<array<int, 26>(int)> dfs = [&](int node) {
            visited[node] = true;
            array<int, 26> count = {0};

            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    array<int, 26> childCount = dfs(neighbor);
                    for (int i = 0; i < 26; ++i) {
                        count[i] += childCount[i];
                    }
                }
            }

            count[labels[node] - 'a']++;
            result[node] = count[labels[node] - 'a'];
            return count;
        };

        dfs(0);
        return result;          
    }
};
