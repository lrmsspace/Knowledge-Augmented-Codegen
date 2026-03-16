// Source: https://leetcode.com/problems/path-sum-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.
//
// The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).
//
// Example:
// Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
// Output: 3
// Explanation: The paths that sum to 8 are shown.
//
// Constraints:
// The number of nodes in the tree is in the range [0, 1000].
// 	-109 <= Node.val <= 109
// 	-1000 <= targetSum <= 1000
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
 * @param {number} targetSum
 * @return {number}
 */
var pathSum = function(root, targetSum) {
    let count = 0;

    const dfs = (node, currentPath) => {
        if (!node) return;
        currentPath.push(node.val);

        let sum = 0;
        for (let i = currentPath.length - 1; i >= 0; i--) {
            sum += currentPath[i];
            if (sum === targetSum) {
                count++;
            }
        }

        dfs(node.left, currentPath);
        dfs(node.right, currentPath);
        currentPath.pop();
    }
    dfs(root, []);
    return count;
    
};
