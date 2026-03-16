// Source: https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary tree where node values are digits from 1 to 9. A path in the binary tree is said to be pseudo-palindromic if at least one permutation of the node values in the path is a palindrome.
//
// Return the number of pseudo-palindromic paths going from the root node to leaf nodes.
//
// Example:
// Input: root = [2,3,1,3,1,null,1]
// Output: 2 
// Explanation: The figure above represents the given binary tree. There are three paths going from the root node to leaf nodes: the red path [2,3,3], the green path [2,1,1], and the path [2,3,1]. Among these paths only red path and green path are pseudo-palindromic paths since the red path [2,3,3] can be rearranged in [3,2,3] (palindrome) and the green path [2,1,1] can be rearranged in [1,2,1] (palindrome).
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 9
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
    int dfs(TreeNode* node, int path) {
        if (!node) return 0;

        // Toggle the bit corresponding to the current node's value
        path ^= (1 << node->val);

        // If it's a leaf node, check if the path is pseudo-palindromic
        if (!node->left && !node->right) {
            // Check if at most one bit is set in path
            if ((path & (path - 1)) == 0) {
                return 1;
            } else {
                return 0;
            }
        }

        // Continue DFS on left and right children
        return dfs(node->left, path) + dfs(node->right, path);
    }
    int pseudoPalindromicPaths (TreeNode* root) {
        return dfs(root, 0);            
    }
};
