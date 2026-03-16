// Source: https://leetcode.com/problems/evaluate-boolean-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// You are given the root of a full binary tree with the following properties:
//
//
// 	Leaf nodes have either the value 0 or 1, where 0 represents False and 1 represents True.
// 	Non-leaf nodes have either the value 2 or 3, where 2 represents the boolean OR and 3 represents the boolean AND.
//
//
// The evaluation of a node is as follows:
//
//
// 	If the node is a leaf node, the evaluation is the value of the node, i.e. True or False.
// 	Otherwise, evaluate the node's two children and apply the boolean operation of its value with the children's evaluations.
//
//
// Return the boolean result of evaluating the root node.
//
// A full binary tree is a binary tree where each node has either 0 or 2 children.
//
// A leaf node is a node that has zero children.
//
// Example:
// Input: root = [2,1,3,null,null,0,1]
// Output: true
// Explanation: The above diagram illustrates the evaluation process.
// The AND node evaluates to False AND True = False.
// The OR node evaluates to True OR False = True.
// The root node evaluates to True, so we return true.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	0 <= Node.val <= 3
// 	Every node has either 0 or 2 children.
// 	Leaf nodes have a value of 0 or 1.
// 	Non-leaf nodes have a value of 2 or 3.
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
    bool evaluateTree(TreeNode* root) {
        if (!root) return false; // Base case: if the node is null, return false

        // If it's a leaf node, return its value as a boolean
        if (!root->left && !root->right) {
            return root->val == 1; // Return true if val is 1, false if val is 0
        }

        // Recursively evaluate left and right subtrees
        bool leftEval = evaluateTree(root->left);
        bool rightEval = evaluateTree(root->right);

        // Apply the boolean operation based on the current node's value
        if (root->val == 2) { // OR operation
            return leftEval || rightEval;
        } else { // AND operation (root->val == 3)
            return leftEval && rightEval;
        }           
    }
};
