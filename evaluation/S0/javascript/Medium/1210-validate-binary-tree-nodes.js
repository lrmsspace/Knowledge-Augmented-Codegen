// Source: https://leetcode.com/problems/validate-binary-tree-nodes/   |   Difficulty: Medium
//
// Problem Description:
// You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], return true if and only if all the given nodes form exactly one valid binary tree.
//
// If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
//
// Note that the nodes have no values and that we only use the node numbers in this problem.
//
// Example:
// Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
// Output: true
//
// Constraints:
// n == leftChild.length == rightChild.length
// 	1 <= n <= 104
// 	-1 <= leftChild[i], rightChild[i] <= n - 1
//

/**
 * @param {number} n
 * @param {number[]} leftChild
 * @param {number[]} rightChild
 * @return {boolean}
 */
var validateBinaryTreeNodes = function(n, leftChild, rightChild) {
    
    const parent = new Array(n).fill(-1);
    for (let i = 0; i < n; i++) {
        if (leftChild[i] !== -1) {
            if (parent[leftChild[i]] !== -1) return false;
            parent[leftChild[i]] = i;
        }
        if (rightChild[i] !== -1) {
            if (parent[rightChild[i]] !== -1) return false;
            parent[rightChild[i]] = i;
        }   
    }
    
    let rootCount = 0;
    for (let i = 0; i < n; i++) {
        if (parent[i] === -1) rootCount++;
    }
    return rootCount === 1;
};
