// Source: https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value of the destination node t.
//
// Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:
//
//
// 	'L' means to go from a node to its left child node.
// 	'R' means to go from a node to its right child node.
// 	'U' means to go from a node to its parent node.
//
//
// Return the step-by-step directions of the shortest path from node s to node t.
//
// Example:
// Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
// Output: "UURL"
// Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= n
// 	All the values in the tree are unique.
// 	1 <= startValue, destValue <= n
// 	startValue != destValue
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
char* getDirections(struct TreeNode* root, int startValue, int destValue) {
    #define MAXN 100005
    int parent[MAXN] = {0};
    char direction[MAXN] = {0};
    
    // DFS to build parent and direction arrays
    void dfs(struct TreeNode* node, int par, char dir) {
        if (!node) return;
        parent[node->val] = par;
        direction[node->val] = dir;
        dfs(node->left, node->val, 'L');
        dfs(node->right, node->val, 'R');
    }
    dfs(root, -1, ' ');

    // Find the path from startValue to root
    char pathToRootFromStart[MAXN];
    int lenStart = 0;
    int curr = startValue;
    while (curr != -1) {
        pathToRootFromStart[lenStart++] = curr;
        curr = parent[curr];
    }

    // Find the path from destValue to root
    char pathToRootFromDest[MAXN];
    int lenDest = 0;
    curr = destValue;
    while (curr != -1) {
        pathToRootFromDest[lenDest++] = curr;
        curr = parent[curr];
    }

    // Find the lowest common ancestor (LCA)
    int i = lenStart - 1;
    int j = lenDest - 1;
    while (i >= 0 && j >= 0 && pathToRootFromStart[i] == pathToRootFromDest[j]) {
        i--;
        j--;
    }
    
    // Build the result string
    char* result = (char*)malloc((lenStart + lenDest + 1) * sizeof(char));
    int idx = 0;

    // Move up from startValue to LCA
    for (int k = 0; k <= i; k++) {
        result[idx++] = 'U';
    }

    // Move down from LCA to destValue
    for (int k = j + 1; k < lenDest; k++) {
        result[idx++] = direction[pathToRootFromDest[k]];
    }
    
    result[idx] = '\0';
    return result;
}
