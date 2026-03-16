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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool btreeGameWinningMove(struct TreeNode* root, int n, int x) {
    struct TreeNode* stack[101];
    int sizes[101] = {0};
    int top = 0;
    stack[top++] = root;
    int xi = -1;

    while (top) {
        struct TreeNode* node = stack[--top];
        if (node->val == x) {
            xi = node;
        }
        if (node->right) {
            stack[top++] = node->right;
        }
        if (node->left) {
            stack[top++] = node->left;
        }
    }

    int left_size = 0, right_size = 0;
    top = 0;
    stack[top++] = xi->left;
    while (top) {
        struct TreeNode* node = stack[--top];
        left_size++;
        if (node->right) {
            stack[top++] = node->right;
        }
        if (node->left) {
            stack[top++] = node->left;
        }
    }

    top = 0;
    stack[top++] = xi->right;
    while (top) {
        struct TreeNode* node = stack[--top];
        right_size++;
        if (node->right) {
            stack[top++] = node->right;
        }
        if (node->left) {
            stack[top++] = node->left;
        }
    }

    int parent_size = n - left_size - right_size - 1;

    int max_size = left_size > right_size ? left_size : right_size;
    max_size = max_size > parent_size ? max_size : parent_size;

    return max_size > n / 2;        
}
