// Source: https://leetcode.com/problems/merge-bsts-to-create-single-bst/   |   Difficulty: Hard
//
// Problem Description:
// You are given n BST (binary search tree) root nodes for n separate BSTs stored in an array trees (0-indexed). Each BST in trees has at most 3 nodes, and no two roots have the same value. In one operation, you can:
//
//
// 	Select two distinct indices i and j such that the value stored at one of the leaves of trees[i] is equal to the root value of trees[j].
// 	Replace the leaf node in trees[i] with trees[j].
// 	Remove trees[j] from trees.
//
//
// Return the root of the resulting BST if it is possible to form a valid BST after performing n - 1 operations, or null if it is impossible to create a valid BST.
//
// A BST (binary search tree) is a binary tree where each node satisfies the following property:
//
//
// 	Every node in the node's left subtree has a value strictly less than the node's value.
// 	Every node in the node's right subtree has a value strictly greater than the node's value.
//
//
// A leaf is a node that has no children.
//
// Example:
// Input: trees = [[2,1],[3,2,5],[5,4]]
// Output: [3,2,5,1,null,4]
// Explanation:
// In the first operation, pick i=1 and j=0, and merge trees[0] into trees[1].
// Delete trees[0], so trees = [[3,2,5,1],[5,4]].
//
// In the second operation, pick i=0 and j=1, and merge trees[1] into trees[0].
// Delete trees[1], so trees = [[3,2,5,1,null,4]].
//
// The resulting tree, shown above, is a valid BST, so return its root.
//
// Constraints:
// n == trees.length
// 	1 <= n <= 5 * 104
// 	The number of nodes in each tree is in the range [1, 3].
// 	Each node in the input may have children but no grandchildren.
// 	No two roots of trees have the same value.
// 	All the trees in the input are valid BSTs.
// 	1 <= TreeNode.val <= 5 * 104.
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
 * @param {TreeNode[]} trees
 * @return {TreeNode}
 */
var canMerge = function(trees) {
    const rootMap = new Map();
    const leafMap = new Map();
    for (const tree of trees) {
        rootMap.set(tree.val, tree);
        if (tree.left) {
            leafMap.set(tree.left.val, (leafMap.get(tree.left.val) || 0) + 1);
        }
        if (tree.right) {
            leafMap.set(tree.right.val, (leafMap.get(tree.right.val) || 0) + 1);
        }
    }
    let root = null;
    for (const tree of trees) {
        if (!leafMap.has(tree.val)) {
            if (root) {
                return null; // More than one root candidate
            }
            root = tree;
        }
    }
    if (!root) {
        return null; // No root candidate found
    }
    const merge = (node) => {
        if (!node) {
            return true;
        }
        if (rootMap.has(node.val) && rootMap.get(node.val) !== node) {  
            const mergeNode = rootMap.get(node.val);
            node.left = mergeNode.left;
            node.right = mergeNode.right;
            rootMap.delete(node.val);
        }
        return merge(node.left) && merge(node.right);   
    };
    if (!merge(root) || rootMap.size > 1) {
        return null; // Not all trees were merged successfully
    }
    return root;
};
