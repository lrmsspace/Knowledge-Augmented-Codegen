// Source: https://leetcode.com/problems/kth-smallest-element-in-a-bst/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.
//
// Example:
// Input: root = [3,1,4,null,2], k = 1
// Output: 1
//
// Constraints:
// The number of nodes in the tree is n.
// 	1 <= k <= n <= 104
// 	0 <= Node.val <= 104
//
//
//  
// Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

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
    int kthSmallest(TreeNode* root, int k) {
        int count = 0;
        int result = -1;

        std::function<void(TreeNode*)> inorder = [&](TreeNode* node) {
            if (!node || result != -1) return;

            inorder(node->left);

            count++;
            if (count == k) {
                result = node->val;
                return;
            }

            inorder(node->right);
        };

        inorder(root);
        return result;          
    }
};
