// Source: https://leetcode.com/problems/symmetric-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
//
// Example:
// Input: root = [1,2,2,3,4,4,3]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Could you solve it both recursively and iteratively?
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
 * @return {boolean}
 */
var isSymmetric = function(root) {
    if (!root) return true;

    const isMirror = (t1, t2) => {
        if (!t1 && !t2) return true;
        if (!t1 || !t2) return false;
        return (t1.val === t2.val)
            && isMirror(t1.left, t2.right)
            && isMirror(t1.right, t2.left);
    };

    return isMirror(root.left, root.right);
};
