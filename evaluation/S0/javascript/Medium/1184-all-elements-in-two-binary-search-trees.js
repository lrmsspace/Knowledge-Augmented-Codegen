// Source: https://leetcode.com/problems/all-elements-in-two-binary-search-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given two binary search trees root1 and root2, return a list containing all the integers from both trees sorted in ascending order.
//
// Example:
// Input: root1 = [2,1,4], root2 = [1,0,3]
// Output: [0,1,1,2,3,4]
//
// Constraints:
// The number of nodes in each tree is in the range [0, 5000].
// 	-105 <= Node.val <= 105
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
 * @param {TreeNode} root1
 * @param {TreeNode} root2
 * @return {number[]}
 */
var getAllElements = function(root1, root2) {
    const inorderTraversal = (node, result) => {
        if (!node) return;
        inorderTraversal(node.left, result);
        result.push(node.val);
        inorderTraversal(node.right, result);
    };
    const list1 = [];
    const list2 = [];
    inorderTraversal(root1, list1);
    inorderTraversal(root2, list2);
    const mergedList = [];
    let i = 0, j = 0;
    while (i < list1.length && j < list2.length) {
        if (list1[i] < list2[j]) {
            mergedList.push(list1[i]);
            i++;
        } else {
            mergedList.push(list2[j]);
            j++;
        }
    }
    while (i < list1.length) {
        mergedList.push(list1[i]);
        i++;
    }
    while (j < list2.length) {
        mergedList.push(list2[j]);
        j++;
    }
    return mergedList;
        
};
