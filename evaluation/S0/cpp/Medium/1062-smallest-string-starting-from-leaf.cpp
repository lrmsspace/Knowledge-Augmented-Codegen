// Source: https://leetcode.com/problems/smallest-string-starting-from-leaf/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree where each node has a value in the range [0, 25] representing the letters 'a' to 'z'.
//
// Return the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
//
// As a reminder, any shorter prefix of a string is lexicographically smaller.
//
//
// 	For example, "ab" is lexicographically smaller than "aba".
//
//
// A leaf of a node is a node that has no children.
//
// Example:
// Input: root = [0,1,2,3,4,3,4]
// Output: "dba"
//
// Constraints:
// The number of nodes in the tree is in the range [1, 8500].
// 	0 <= Node.val <= 25
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
    string smallestFromLeaf(TreeNode* root) {
        string result = "~"; // '~' is lexicographically larger than 'z'

        function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string path) {
            if (!node) return;

            path.push_back('a' + node->val);

            if (!node->left && !node->right) {
                reverse(path.begin(), path.end());
                result = min(result, path);
                reverse(path.begin(), path.end());
            }

            dfs(node->left, path);
            dfs(node->right, path);
        };

        dfs(root, "");
        return result;          
    }
};
