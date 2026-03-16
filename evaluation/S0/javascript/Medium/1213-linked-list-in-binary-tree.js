// Source: https://leetcode.com/problems/linked-list-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary tree root and a linked list with head as the first node. 
//
// Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.
//
// In this context downward path means a path that starts at some node and goes downwards.
//
// Example:
// Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
// Output: true
// Explanation: Nodes in blue form a subpath in the binary Tree.
//
// Constraints:
// The number of nodes in the tree will be in the range [1, 2500].
// 	The number of nodes in the list will be in the range [1, 100].
// 	1 <= Node.val <= 100 for each node in the linked list and binary tree.
//

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {ListNode} head
 * @param {TreeNode} root
 * @return {boolean}
 */
var isSubPath = function(head, root) {
    if (!head) return true;
    if (!root) return false;

    const dfs = (listNode, treeNode) => {
        if (!listNode) return true;
        if (!treeNode) return false;    
        if (listNode.val !== treeNode.val) return false;

        return dfs(listNode.next, treeNode.left) || dfs(listNode.next, treeNode.right);
    }
        
    return dfs(head, root) || isSubPath(head, root.left) || isSubPath(head, root.right);
};
