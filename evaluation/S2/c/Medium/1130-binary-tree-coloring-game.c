// Source: https://leetcode.com/problems/binary-tree-coloring-game/   |   Difficulty: Medium
//
// Problem Description:
// Two players play a turn based game on a binary tree. We are given the root of this binary tree, and the number of nodes n in the tree. n is odd, and each node has a distinct value from 1 to n.
//
// Initially, the first player names a value x with 1 <= x <= n, and the second player names a value y with 1 <= y <= n and y != x. The first player colors the node with value x red, and the second player colors the node with value y blue.
//
// Then, the players take turns starting with the first player. In each turn, that player chooses a node of their color (red if player 1, blue if player 2) and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)
//
// If (and only if) a player cannot choose such a node in this way, they must pass their turn. If both players pass their turn, the game ends, and the winner is the player that colored more nodes.
//
// You are the second player. If it is possible to choose such a y to ensure you win the game, return true. If it is not possible, return false.
//
// Example:
// Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
// Output: true
// Explanation: The second player can choose the node with value 2.
//
// Constraints:
// The number of nodes in the tree is n.
// 	1 <= x <= n <= 100
// 	n is odd.
// 	1 <= Node.val <= n
// 	All the values of the tree are unique.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool btreeGameWinningMove(struct TreeNode* root, int n, int x) {
    struct TreeNode *xNode = NULL;
    int leftCount = 0, rightCount = 0;

    // Helper function to find the node with value x and count the nodes in its left and right subtrees
    void countNodes(struct TreeNode* node) {
        if (!node) return;
        if (node->val == x) {
            xNode = node;
            return;
        }
        countNodes(node->left);
        countNodes(node->right);
    }

    countNodes(root);

    // Count the nodes in the left and right subtrees of xNode
    int countSubtree(struct TreeNode* node) {
        if (!node) return 0;
        return 1 + countSubtree(node->left) + countSubtree(node->right);
    }

    if (xNode) {
        leftCount = countSubtree(xNode->left);
        rightCount = countSubtree(xNode->right);
    }

    int parentCount = n - (leftCount + rightCount + 1); // Nodes not in x's subtree

    // The second player can win if they can choose a subtree with more than half of the nodes
    return (leftCount > n / 2) || (rightCount > n / 2) || (parentCount > n / 2);        
}
