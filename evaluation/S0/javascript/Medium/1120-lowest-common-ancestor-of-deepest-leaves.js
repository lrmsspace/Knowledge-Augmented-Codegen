// Source: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.
//
// Recall that:
//
//
// 	The node of a binary tree is a leaf if and only if it has no children
// 	The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its children is d + 1.
// 	The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that every node in S is in the subtree with root A.
//
// Example:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4]
// Output: [2,7,4]
// Explanation: We return the node with value 2, colored in yellow in the diagram.
// The nodes coloured in blue are the deepest leaf-nodes of the tree.
// Note that nodes 6, 0, and 8 are also leaf nodes, but the depth of them is 2, but the depth of nodes 7 and 4 is 3.
//
// Constraints:
// The number of nodes in the tree will be in the range [1, 1000].
// 	0 <= Node.val <= 1000
// 	The values of the nodes in the tree are unique.
//
//
//  
// Note: This question is the same as 865: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
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
var lcaDeepestLeaves = function(root) {
    function helper(node) {
        if (!node) return [0, null];
        const [leftDepth, leftLCA] = helper(node.left);
        const [rightDepth, rightLCA] = helper(node.right);
        if (leftDepth > rightDepth) {
            return [leftDepth + 1, leftLCA];
        } else if (rightDepth > leftDepth) {
            return [rightDepth + 1, rightLCA];
        }
        return [leftDepth + 1, node];
    }   
    return helper(root)[1]; 
                
};
