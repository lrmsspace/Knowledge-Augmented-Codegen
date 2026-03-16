// Source: https://leetcode.com/problems/maximum-binary-tree-ii/   |   Difficulty: Medium
//
// Problem Description:
// A maximum tree is a tree where every node has a value greater than any other value in its subtree.
//
// You are given the root of a maximum binary tree and an integer val.
//
// Just as in the previous problem, the given tree was constructed from a list a (root = Construct(a)) recursively with the following Construct(a) routine:
//
//
// 	If a is empty, return null.
// 	Otherwise, let a[i] be the largest element of a. Create a root node with the value a[i].
// 	The left child of root will be Construct([a[0], a[1], ..., a[i - 1]]).
// 	The right child of root will be Construct([a[i + 1], a[i + 2], ..., a[a.length - 1]]).
// 	Return root.
//
//
// Note that we were not given a directly, only a root node root = Construct(a).
//
// Suppose b is a copy of a with the value val appended to it. It is guaranteed that b has unique values.
//
// Return Construct(b).
//
// Example:
// Input: root = [4,1,3,null,null,2], val = 5
// Output: [5,4,null,1,3,null,null,2]
// Explanation: a = [1,4,2,3], b = [1,4,2,3,5]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
// 	1 <= Node.val <= 100
// 	All the values of the tree are unique.
// 	1 <= val <= 100
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
 * @param {number} val
 * @return {TreeNode}
 */
var insertIntoMaxTree = function(root, val) {
    if (!root || val > root.val) {
        const newNode = new TreeNode(val);
        newNode.left = root;
        return newNode;
    } else {
        root.right = insertIntoMaxTree(root.right, val);
        return root;
    }   
            
};
