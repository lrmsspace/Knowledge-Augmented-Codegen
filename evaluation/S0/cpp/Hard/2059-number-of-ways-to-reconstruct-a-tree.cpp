// Source: https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array pairs, where pairs[i] = [xi, yi], and:
//
//
// 	There are no duplicates.
// 	xi < yi
//
//
// Let ways be the number of rooted trees that satisfy the following conditions:
//
//
// 	The tree consists of nodes whose values appeared in pairs.
// 	A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
// 	Note: the tree does not have to be a binary tree.
//
//
// Two ways are considered to be different if there is at least one node that has different parents in both ways.
//
// Return:
//
//
// 	0 if ways == 0
// 	1 if ways == 1
// 	2 if ways > 1
//
//
// A rooted tree is a tree that has a single root node, and all edges are oriented to be outgoing from the root.
//
// An ancestor of a node is any node on the path from the root to that node (excluding the node itself). The root has no ancestors.
//
// Example:
// Input: pairs = [[1,2],[2,3]]
// Output: 1
// Explanation: There is exactly one valid rooted tree, which is shown in the above figure.
//
// Constraints:
// 1 <= pairs.length <= 105
// 	1 <= xi < yi <= 500
// 	The elements in pairs are unique.
//

class Solution {
public:
    int checkWays(vector<vector<int>>& pairs) {
        const int MAXN = 501;
        vector<unordered_set<int>> graph(MAXN);
        unordered_set<int> nodes;
        
        // Build the graph
        for (const auto& p : pairs) {
            graph[p[0]].insert(p[1]);
            graph[p[1]].insert(p[0]);
            nodes.insert(p[0]);
            nodes.insert(p[1]);
        }
        
        int root = -1;
        for (int node : nodes) {
            if (graph[node].size() == nodes.size() - 1) {
                root = node;
                break;
            }
        }
        
        if (root == -1) return 0;  // No valid root found
        
        int result = 1;
        
        for (int node : nodes) {
            if (node == root) continue;
            
            int parent = -1;
            int parentDegree = INT_MAX;
            
            for (int neighbor : graph[node]) {
                if (graph[neighbor].size() >= graph[node].size() && graph[neighbor].size() < parentDegree) {
                    parent = neighbor;
                    parentDegree = graph[neighbor].size();
                }
            }
            
            if (parent == -1) return 0;  // No valid parent found
            
            for (int neighbor : graph[node]) {
                if (neighbor != parent && graph[parent].find(neighbor) == graph[parent].end()) {
                    return 0;  // Missing connection
                }
            }
            
            if (parentDegree == graph[node].size()) {
                result = 2;  // Multiple ways possible
            }
        }
        
        return result;          
    }
};
