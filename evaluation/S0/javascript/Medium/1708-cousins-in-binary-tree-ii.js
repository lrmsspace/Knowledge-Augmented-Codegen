// Source: https://leetcode.com/problems/cousins-in-binary-tree-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, replace the value of each node in the tree with the sum of all its cousins' values.
//
// Two nodes of a binary tree are cousins if they have the same depth with different parents.
//
// Return the root of the modified tree.
//
// Note that the depth of a node is the number of edges in the path from the root node to it.
//
// Example:
// Input: root = [5,4,9,1,10,null,7]
// Output: [0,0,0,7,7,null,11]
// Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
// - Node with value 5 does not have any cousins so its sum is 0.
// - Node with value 4 does not have any cousins so its sum is 0.
// - Node with value 9 does not have any cousins so its sum is 0.
// - Node with value 1 has a cousin with value 7 so its sum is 7.
// - Node with value 10 has a cousin with value 7 so its sum is 7.
// - Node with value 7 has cousins with values 1 and 10 so its sum is 11.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 104
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
 * @return {TreeNode}
 */
var replaceValueInTree = function(root) {
    if (!root) return null;
    const queue = [root];
    root.val = 0;
    while (queue.length) {
        const levelSize = queue.length;
        let levelSum = 0;
        const siblingsSum = new Map();
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            let siblingSum = 0;
            if (node.left) {
                siblingSum += node.left.val;
                queue.push(node.left);
            }
            if (node.right) {
                siblingSum += node.right.val;
                queue.push(node.right);
            }
            siblingsSum.set(node, siblingSum);
            levelSum += siblingSum;
        }
        for (let i = 0; i < levelSize; i++) {
            const node = queue[i - levelSize];
            const siblingSum = siblingsSum.get(node);
            if (node.left) {
                node.left.val = levelSum - siblingSum;
            }
            if (node.right) {
                node.right.val = levelSum - siblingSum;
            }
        }
    }
    return root;    
                
};
