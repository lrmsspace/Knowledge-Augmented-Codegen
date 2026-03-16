// Source: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
//
// For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).
//
// The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.
//
// Return the vertical order traversal of the binary tree.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: [[9],[3,15],[20],[7]]
// Explanation:
// Column -1: Only node 9 is in this column.
// Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
// Column 1: Only node 20 is in this column.
// Column 2: Only node 7 is in this column.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	0 <= Node.val <= 1000
//

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {number[][]}
 */
var verticalTraversal = function(root) {
    const columnTable = new Map();

    const dfs = (node, row, col) => {
        if (!node) return;
        if (!columnTable.has(col)) {
            columnTable.set(col, []);
        }
        columnTable.get(col).push([row, node.val]);
        dfs(node.left, row + 1, col - 1);
        dfs(node.right, row + 1, col + 1);
    };

    dfs(root, 0, 0);

    const sortedColumns = Array.from(columnTable.keys()).sort((a, b) => a - b);
    const result = [];

    for (const col of sortedColumns) {
        const nodes = columnTable.get(col);
        nodes.sort((a, b) => a[0] === b[0] ? a[1] - b[1] : a[0] - b[0]);
        result.push(nodes.map(([_, val]) => val));
    }

    return result;
};
