// Source: https://leetcode.com/problems/print-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, construct a 0-indexed m x n string matrix res that represents a formatted layout of the tree. The formatted layout matrix should be constructed using the following rules:
//
//
// 	The height of the tree is height and the number of rows m should be equal to height + 1.
// 	The number of columns n should be equal to 2height+1 - 1.
// 	Place the root node in the middle of the top row (more formally, at location res[0][(n-1)/2]).
// 	For each node that has been placed in the matrix at position res[r][c], place its left child at res[r+1][c-2height-r-1] and its right child at res[r+1][c+2height-r-1].
// 	Continue this process until all the nodes in the tree have been placed.
// 	Any empty cells should contain the empty string "".
//
//
// Return the constructed matrix res.
//
// Example:
// Input: root = [1,2]
// Output: 
// [["","1",""],
//  ["2","",""]]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 210].
// 	-99 <= Node.val <= 99
// 	The depth of the tree will be in the range [1, 10].
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** printTree(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    // Helper function to calculate the height of the tree
    int height(struct TreeNode* node) {
        if (!node) return -1;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    // Helper function to fill the matrix
    void fill(char*** res, struct TreeNode* node, int r, int c, int h) {
        if (!node) return;
        char buffer[12];
        sprintf(buffer, "%d", node->val);
        res[r][c] = strdup(buffer);
        fill(res, node->left, r + 1, c - (1 << (h - r - 1)), h);
        fill(res, node->right, r + 1, c + (1 << (h - r - 1)), h);
    }

    int h = height(root);
    int m = h + 1;
    int n = (1 << (h + 1)) - 1;

    // Allocate memory for the result matrix
    char*** res = (char***)malloc(m * sizeof(char**));
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        res[i] = (char**)malloc(n * sizeof(char*));
        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++) {
            res[i][j] = strdup("");
        }
    }

    // Fill the matrix with tree values
    fill(res, root, 0, (n - 1) / 2, h);

    *returnSize = m;
    return res;     
}
