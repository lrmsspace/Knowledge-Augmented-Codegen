// Source: https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with unique values.
//
// In one operation, you can choose any two nodes at the same level and swap their values.
//
// Return the minimum number of operations needed to make the values at each level sorted in a strictly increasing order.
//
// The level of a node is the number of edges along the path between it and the root node.
//
// Example:
// Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
// Output: 3
// Explanation:
// - Swap 4 and 3. The 2nd level becomes [3,4].
// - Swap 7 and 5. The 3rd level becomes [5,6,8,7].
// - Swap 8 and 7. The 3rd level becomes [5,6,7,8].
// We used 3 operations so return 3.
// It can be proven that 3 is the minimum number of operations needed.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	All the values of the tree are unique.
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
 * @return {number}
 */
var minimumOperations = function(root) {
    let totalOperations = 0;
    const queue = [root];
    while (queue.length > 0) {
        const levelSize = queue.length;
        const levelValues = [];
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            levelValues.push(node.val);
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
        totalOperations += minSwapsToSort(levelValues);
    }
    return totalOperations;
};

function minSwapsToSort(arr) {
    const n = arr.length;
    const arrPos = arr.map((value, index) => [value, index]);
    arrPos.sort((a, b) => a[0] - b[0]);
    const visited = new Array(n).fill(false);
    let swaps = 0;
    for (let i = 0; i < n; i++) {
        if (visited[i] || arrPos[i][1] === i) continue;
        let cycleSize = 0;
        let j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = arrPos[j][1];
            cycleSize++;
        }
        if (cycleSize > 0) swaps += (cycleSize - 1);
    }
    return swaps;
}