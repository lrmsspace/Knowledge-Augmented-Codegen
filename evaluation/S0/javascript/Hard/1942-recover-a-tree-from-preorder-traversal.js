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
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {string} traversal
 * @return {TreeNode}
 */
var recoverFromPreorder = function(traversal) {
    const stack = [];
    let i = 0;  
    while (i < traversal.length) {
        let depth = 0;
        while (i < traversal.length && traversal[i] === '-') {
            depth++;
            i++;
        }
        let value = 0;
        while (i < traversal.length && traversal[i] !== '-') {
            value = value * 10 + (traversal[i] - '0');
            i++;
        }
        const node = new TreeNode(value);
        while (stack.length > depth) {
            stack.pop();
        }
        if (stack.length > 0) {
            if (!stack[stack.length - 1].left) {
                stack[stack.length - 1].left = node;
            } else {
                stack[stack.length - 1].right = node;
            }
        }
        stack.push(node);
    }
    return stack[0];    
};
