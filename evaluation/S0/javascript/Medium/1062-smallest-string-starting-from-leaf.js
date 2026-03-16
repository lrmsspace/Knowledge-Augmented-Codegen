// Source: https://leetcode.com/problems/smallest-string-starting-from-leaf/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree where each node has a value in the range [0, 25] representing the letters 'a' to 'z'.
//
// Return the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
//
// As a reminder, any shorter prefix of a string is lexicographically smaller.
//
//
// 	For example, "ab" is lexicographically smaller than "aba".
//
//
// A leaf of a node is a node that has no children.
//
// Example:
// Input: root = [0,1,2,3,4,3,4]
// Output: "dba"
//
// Constraints:
// The number of nodes in the tree is in the range [1, 8500].
// 	0 <= Node.val <= 25
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
 * @return {string}
 */
var smallestFromLeaf = function(root) {
    let result = null;
    const dfs = (node, path) => {
        if (!node) return;
        path.push(String.fromCharCode(97 + node.val));
        if (!node.left && !node.right) {
            const candidate = path.slice().reverse().join('');
            if (result === null || candidate < result) {
                result = candidate;
            }
        } else {
            dfs(node.left, path);
            dfs(node.right, path);
        }
        path.pop();
    };
    dfs(root, []);
    return result;  
        
};
