// Source: https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given the root of a binary tree with n nodes. Each node is assigned a unique value from 1 to n. You are also given an array queries of size m.
//
// You have to perform m independent queries on the tree where in the ith query you do the following:
//
//
// 	Remove the subtree rooted at the node with the value queries[i] from the tree. It is guaranteed that queries[i] will not be equal to the value of the root.
//
//
// Return an array answer of size m where answer[i] is the height of the tree after performing the ith query.
//
// Note:
//
//
// 	The queries are independent, so the tree returns to its initial state after each query.
// 	The height of a tree is the number of edges in the longest simple path from the root to some node in the tree.
//
// Example:
// Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
// Output: [2]
// Explanation: The diagram above shows the tree after removing the subtree rooted at node with value 4.
// The height of the tree is 2 (The path 1 -> 3 -> 2).
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= n
// 	All the values in the tree are unique.
// 	m == queries.length
// 	1 <= m <= min(n, 104)
// 	1 <= queries[i] <= n
// 	queries[i] != root.val
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        int n = 0;
        unordered_map<int, vector<int>> adj;
        unordered_map<int, int> parent;
        unordered_map<int, int> depth;
        unordered_map<int, int> height;
        
        // Build tree as adjacency list and record parent and depth
        function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int par, int d) {
            if (!node) return;
            n++;
            depth[node->val] = d;
            parent[node->val] = par;
            if (par != -1) {
                adj[par].push_back(node->val);
            }
            dfs(node->left, node->val, d + 1);
            dfs(node->right, node->val, d + 1);
        };
        
        dfs(root, -1, 0);
        
        // Compute height of each subtree
        function<int(int)> computeHeight = [&](int u) {
            int h = 0;
            for (int v : adj[u]) {
                h = max(h, computeHeight(v) + 1);
            }
            height[u] = h;
            return h;
        };
        
        computeHeight(root->val);
        
        // Precompute the maximum heights excluding each child
        unordered_map<int, vector<int>> maxExclChild;
        
        function<void(int)> precomputeMaxExcl = [&](int u) {
            vector<int> childHeights;
            for (int v : adj[u]) {
                childHeights.push_back(height[v]);
            }
            
            int m = childHeights.size();
            vector<int> prefixMax(m + 1, -1), suffixMax(m + 1, -1);
            
            for (int i = 0; i < m; i++) {
                prefixMax[i + 1] = max(prefixMax[i], childHeights[i]);
            }
            for (int i = m - 1; i >= 0; i--) {
                suffixMax[i] = max(suffixMax[i + 1], childHeights[i]);
            }
            
            for (int i = 0; i < m; i++) {
                maxExclChild[u].push_back(max(prefixMax[i], suffixMax[i + 1]));
            }
            
            for (int v : adj[u]) {
                precomputeMaxExcl(v);
            }
        };   
        precomputeMaxExcl(root->val);
        vector<int> result;
        for (int q : queries) {
            int par = parent[q];
            if (par == -1) {
                result.push_back(0);
                continue;
            }
            int idx = -1;
            for (int i = 0; i < adj[par].size(); i++) {
                if (adj[par][i] == q) {
                    idx = i;
                    break;
                }
            }
            int exclHeight = maxExclChild[par][idx];
            int newHeight = depth[par] + (exclHeight == -1 ? 0 : exclHeight + 1);
            result.push_back(newHeight);
        }
        return result;       
    }
};
