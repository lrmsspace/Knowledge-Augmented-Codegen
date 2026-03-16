// Source: https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/   |   Difficulty: Hard
//
// Problem Description:
// We run a preorder depth-first search (DFS) on the root of a binary tree.
//
// At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  If the depth of a node is D, the depth of its immediate child is D + 1.  The depth of the root node is 0.
//
// If a node has only one child, that child is guaranteed to be the left child.
//
// Given the output traversal of this traversal, recover the tree and return its root.
//
// Example:
// Input: traversal = "1-2--3--4-5--6--7"
// Output: [1,2,5,3,4,6,7]
//
// Constraints:
// The number of nodes in the original tree is in the range [1, 1000].
// 	1 <= Node.val <= 109
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
    TreeNode* recoverFromPreorder(string traversal) {
        int idx = 0;
        return recover(traversal, idx, 0);          
    }
};
